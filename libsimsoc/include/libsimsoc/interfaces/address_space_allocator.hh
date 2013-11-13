/*
 *  Copyright (c) 2008,
 *  Institut National de Recherche en Informatique et Automatique (INRIA)
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *
 *   - Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *   - Neither the name of the INRIA nor the names of its contributors may be used to
 *     endorse or promote products derived from this software without specific prior
 *     written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE INRIA AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED.
 *  IN NO EVENT SHALL THE INRIA OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 *  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Olivier Certner (olivier.certner@inria.fr)
 */

// Deque
#include <deque>

// Algos
#include <algorithm>

//#define ADDR_SP_ALLOC_DEBUG

#ifdef ADDR_SP_ALLOC_DEBUG
// cerr
#include <iostream>
using std::cerr;
using std::endl;
#endif

//modified for simsoc
namespace simsoc
{
  /**
   * Template class that represents a range of address space.
   *
   * Ranges are multiple of 'words' (the minimum addressable
   * data size).
   */
  template <class ADDRESS_TYPE>
  struct AddressSpaceRange
  {
    typedef AddressSpaceRange<ADDRESS_TYPE> MyType;

    AddressSpaceRange (ADDRESS_TYPE start, ADDRESS_TYPE end)
      : start (start), end (end)
    {}

    AddressSpaceRange () : start (0), end (0)
    {}

    AddressSpaceRange (MyType const & oth)
    {
      * this = oth;
    }

    MyType & operator= (MyType const & oth)
    {
      start = oth.start;
      end = oth.end;
      return * this;
    }

    bool operator== (MyType const & oth) const
    {
      return (start == oth.start && end == oth.end);
    }

    bool operator!= (MyType const & oth) const
    {
      return (start != oth.start || end != oth.end);
    }

    bool operator! () const
    {
      return (start == end);
    }


    /**
     * Beginning of the range (included).
     */
    ADDRESS_TYPE start;

    /**
     * End of the range (not included).
     */
    ADDRESS_TYPE end;
  };

  /**
   * Template class used to compare AddressSpaceRange by start address.
   */
  template <class ADDRESS_TYPE>
  struct AddressSpaceRangeStartCompare
  {
    typedef AddressSpaceRange<ADDRESS_TYPE> RangeType;

    bool operator() (RangeType const & first, RangeType const & second)
    {
      return first.start < second.start;
    }
  };


  /**
   * Template class used to compare AddressSpaceRange by range size.
   */
  template <class ADDRESS_TYPE>
  struct AddressSpaceRangeSizeCompare
  {
    typedef AddressSpaceRange<ADDRESS_TYPE> RangeType;

    bool operator() (RangeType const & first, RangeType const & second)
    {
      ADDRESS_TYPE sum_1, sum_2;
      bool sum_1_ofw, sum_2_ofw;

      sum_1 = first.end + second.start;
      sum_2 = second.end + first.start;

      sum_1_ofw = (sum_1 < first.end);
      sum_2_ofw = (sum_2 < first.start);

      if (~ (sum_1_ofw ^ sum_2_ofw))
        return sum_1 > sum_2;
      else if (sum_1_ofw)
        return true;
      else
        return false;
    }
  };

  // Helper function to coalesce ranges
  template <class IntDequeType, class IntDequeItType, class ADDRESS_TYPE, class RangeType>
  IntDequeItType InsertAndCoalesceRanges (IntDequeType & deque,
                                          IntDequeItType & cur,
                                          RangeType const & range)
  {
    // We only have to coalesce with the 2 neighbors,
    // since we assume the other elements in the deques
    // are always coalesced appropriately.

    IntDequeItType begin = deque.begin ();
    IntDequeItType end = deque.end ();
    IntDequeItType prev = cur - 1;
    // The iterator to return, that points to the range in
    // which the given range is contained after
    // coalescence.
    IntDequeItType ret_it;

    // Did we actually coalesce ranges?
    bool coal = false;

    if (cur != begin)
      if (prev -> end == range.start)
        coal = true;

    if (cur != end)
      {
        ADDRESS_TYPE next_start = cur -> start;

        if (next_start == range.end)
          {
            if (coal)
              {
                // The new range bridges the gap
                // between two previous adjacent
                // ranges. We have to update one of
                // them and remove the other from the
                // list. We choose to update prev and
                // erase cur.
                prev -> end = cur -> end;
                ret_it = deque.erase (cur);
                -- ret_it;
              }
            else
              {
                cur -> start = range.start;
                ret_it = cur;
              }

            coal = true;
          }
        else
          if (coal)
            {
              prev -> end = range.end;
              ret_it = prev;
            }

      } // if (cur != end)
    else
      if (coal)
        {
          prev -> end = range.end;
          ret_it = prev;
        }

    if (! coal)
      // If we didn't coalesce, we just have to insert
      // the range at the right place.
      ret_it = deque.insert (cur, range);

    return ret_it;
  }

  using std::deque;
  using std::lower_bound;
  using std::upper_bound;

  /**
   * Template class that can manage/release contiguous blocks of address space.
   *
   * The ADDRESS_TYPE type parameter indicates the type used to store addresses.
   */
  template <class ADDRESS_TYPE>
  struct AddressSpaceAllocator
  {
    typedef AddressSpaceRange<ADDRESS_TYPE> RangeType;
    typedef AddressSpaceAllocator<ADDRESS_TYPE> MyType;
    typedef AddressSpaceRangeSizeCompare<ADDRESS_TYPE> SizeCompareType;
    typedef AddressSpaceRangeStartCompare<ADDRESS_TYPE> StartCompareType;


    AddressSpaceAllocator (RangeType const & init_range)
    {
      if (! init_range)
        throw 314;

      free_ranges_by_size.push_front (init_range);
      free_ranges.push_front (init_range);

#ifdef ADDR_SP_ALLOC_DEBUG
      cerr << "AddressSpaceAllocator constructor." << endl;
      PrintInternalData ();
#endif
    }

    ~AddressSpaceAllocator ()
    {
#ifdef ADDR_SP_ALLOC_DEBUG
      cerr << "AddressSpaceAllocator constructor." << endl;
      PrintInternalData ();
#endif
    }

    /**
     * Allocates a range of addresses with a given size.
     *
     * \return
     * 'true' if such a range is available, 'false' if not.
     *
     * \param[in]
     * The size of address range to return.
     *
     * \param[out] return_range
     * Returned ranged. Modified only if the method returns true.
     */
    bool AllocRange (ADDRESS_TYPE size, RangeType & return_range)
    {
#ifdef ADDR_SP_ALLOC_DEBUG
      cerr << "AllocRange starting..." << endl;
      PrintInternalData ();
#endif

      // Non-zero length check
      if (! size)
        return false;

      // Temp range used to search appropriately sized range.
      RangeType tmp_range (0, size);
      SizeCompareType size_comp;
      IntDequeItType beg = free_ranges_by_size.begin ();
      IntDequeItType end = free_ranges_by_size.end ();
      IntDequeItType it = upper_bound (beg, end, tmp_range, size_comp);

      // Did we find a large enough free range?
      if (it != beg)
        {
          // Yes
          -- it;

          // We split the candidate range, to return only the length asked for.

          // Compute boundary addresses
          // The used range will start at the beginning of the free range.
          ADDRESS_TYPE start_addr = it -> start;
          ADDRESS_TYPE end_addr = it -> start + size; // We know this can't overflow.
          ADDRESS_TYPE left_end_addr = it -> end;

          // Fill in the range to return
          return_range.start = start_addr;
          return_range.end = end_addr;

          // Insert the range to return in the used ranges container.
          StartCompareType start_comp;
          IntDequeItType beg_used = used_ranges.begin ();
          IntDequeItType end_used = used_ranges.end ();
          IntDequeItType it_used = lower_bound (beg_used, end_used, return_range, start_comp);
          (void) InsertAndCoalesceRanges<IntDequeType, IntDequeItType, ADDRESS_TYPE, RangeType>
            (used_ranges, it_used, return_range);

          // Replace or erase the candidate range.
          IntDequeItType const beg_2 = free_ranges.begin ();
          IntDequeItType const end_2 = free_ranges.end ();
          IntDequeItType it_2 = lower_bound (beg_2, end_2, * it, start_comp);

          // Sanity check
          if (* it_2 != * it)
            throw 314;

          if (left_end_addr != end_addr)
            {
              // Range representing the portion of the found range that is left free
              RangeType left_range (end_addr, left_end_addr);

              // We directly change it, because we know this will preserve start address order.
              * it_2 = left_range;

              // Have to insert it at the right place
              // No coalescence necessary here
              (void) free_ranges_by_size.erase (it);
              beg = free_ranges_by_size.begin ();
              end = free_ranges_by_size.end ();
              it = lower_bound (beg, end, left_range, size_comp);
              free_ranges_by_size.insert (it, left_range);
            }
          else
            {
              (void) free_ranges.erase (it_2);
              (void) free_ranges_by_size.erase (it);
            }

          // Return
#ifdef ADDR_SP_ALLOC_DEBUG
          cerr << "AllocRange ending..." << endl;
          PrintInternalData ();
#endif
          return true;
        }
      else
        {
#ifdef ADDR_SP_ALLOC_DEBUG
          cerr << "AllocRange ending..." << endl;
          PrintInternalData ();
#endif
          return false;
        }
    }

    /**
     * Frees a range of adresses.
     *
     * \param[in] range
     * The range to free. This range of adresses must have
     * been allocated before with AllocRange. Coalesced
     * ranges or sub-ranges from ones returned by
     * AllocRange are perfectly acceptable and will work
     * as expected.
     *
     * \return
     * 'true' if the given address range had been
     * allocated before, 'false' if part of it was not/is
     * no more marked as allocated.
     */
    bool FreeRange (RangeType const & range)
    {
#ifdef ADDR_SP_ALLOC_DEBUG
      cerr << "FreeRange starting..." << endl;
      PrintInternalData ();
#endif

      // Non-zero length check
      if (! range)
        return false;

      StartCompareType start_comp;
      IntDequeItType const beg = used_ranges.begin ();
      IntDequeItType const end = used_ranges.end ();
      IntDequeItType it = upper_bound (beg, end, range, start_comp);

      if (it != beg)
        {
          // We have a candidate
          -- it;

          // Are 'end' bounds compatible?
          ADDRESS_TYPE cand_end = it -> end;

          if (cand_end < range.end)
            {
#ifdef ADDR_SP_ALLOC_DEBUG
              cerr << "FreeRange ending..." << endl;
              PrintInternalData ();
#endif

              // No
              return false;
            }
          else
            {
              // So far, so good. Now, we have to split
              // the candidate to reflect that just
              // 'range' has been freed.
              ADDRESS_TYPE cand_beg = it -> start;
              bool cur_struct_reused;

              if (cand_beg != range.start)
                {
                  cur_struct_reused = true;
                  it -> end = range.start;
                }
              else
                cur_struct_reused = false;

              if (cand_end != range.end)
                {
                  if (cur_struct_reused)
                    {
                      RangeType new_range (range.end, cand_end);
                      ++ it;
                      (void) used_ranges.insert (it, new_range);
                    }
                  else
                    it -> start = range.end;

                  cur_struct_reused = true;
                }

              if (! cur_struct_reused)
                (void) used_ranges.erase (it);

              // Finally, put 'range' in the free deques
              // First, put it in the start-ordered deque and coalesce.
              IntDequeItType fr_beg = free_ranges.begin ();
              IntDequeItType fr_end = free_ranges.end ();
              IntDequeItType fr_it = lower_bound (fr_beg, fr_end, range, start_comp);
              fr_it = InsertAndCoalesceRanges<IntDequeType, IntDequeItType, ADDRESS_TYPE, RangeType>
                (free_ranges, fr_it, range);

              // Not optimal at all, because here we
              // rebuild the whole free ranges by size
              // deque. But anyway, no more time...
              free_ranges_by_size = free_ranges;
              SizeCompareType size_comp;
              IntDequeItType fr_size_beg = free_ranges_by_size.begin ();
              IntDequeItType fr_size_end = free_ranges_by_size.end ();
              sort (fr_size_beg, fr_size_end, size_comp);

              // Return!!
#ifdef ADDR_SP_ALLOC_DEBUG
              cerr << "FreeRange ending..." << endl;
              PrintInternalData ();
#endif
              return true;
            }
        }
      else
        {
#ifdef ADDR_SP_ALLOC_DEBUG
          cerr << "FreeRange ending..." << endl;
          PrintInternalData ();
#endif

          // No acceptable candidate
          return false;
        }
    }

  private:
    typedef deque<RangeType> IntDequeType;
    typedef typename IntDequeType::iterator IntDequeItType;

    // Ordered (by start address) and coalesced (if possible) used address ranges
    IntDequeType used_ranges;
    // Ordered (by start address) and coalesced free address ranges
    IntDequeType free_ranges;
    // Ordered (by descending size) free address ranges
    IntDequeType free_ranges_by_size;

#ifdef ADDR_SP_ALLOC_DEBUG
    void PrintDeque (IntDequeType & deq)
    {
      IntDequeItType beg_it = deq.begin ();
      IntDequeItType end_it = deq.end ();
      IntDequeItType it = beg_it;

      for (; it != end_it; ++ it)
        cerr << " [" << hex<< it -> start << ";" << hex << it -> end << "]" << endl;
    }

    void PrintInternalData ()
    {
      cerr << "Free ranges:" << endl;
      PrintDeque (free_ranges);
      cerr << "Free ranges by size:" << endl;
      PrintDeque (free_ranges_by_size);
      cerr << "Used ranges:" << endl;
      PrintDeque (used_ranges);
    }
#endif
  };


} // namespaces simsoc

