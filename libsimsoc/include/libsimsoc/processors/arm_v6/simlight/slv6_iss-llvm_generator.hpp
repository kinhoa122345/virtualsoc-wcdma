void ARMv6_LLVM_Generator::generate_one_instruction(SLv6_Instruction &instr) {
  switch (instr.args.g0.id) {
  case SLV6_LDR_M2_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_ImmOff"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STR_M2_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_ImmOff"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_B_L1_ID: {
    Function *fct = module->getFunction("slv6_X_B_L1"); assert(fct);
    Value *cond = ConstantInt::get(i32,instr.args.g2.cond);
    Value *pc_offset = ConstantInt::get(i32,instr.args.g2.pc_offset);
    IRB.CreateCall3(fct,proc,cond,pc_offset);
  } break;
  case SLV6_B_L0_ID: {
    Function *fct = module->getFunction("slv6_X_B_L0"); assert(fct);
    Value *cond = ConstantInt::get(i32,instr.args.g2.cond);
    Value *pc_offset = ConstantInt::get(i32,instr.args.g2.pc_offset);
    IRB.CreateCall3(fct,proc,cond,pc_offset);
  } break;
  case SLV6_SUB_M1_Imm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_Imm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SUB_M1_Imm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_Imm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_CMP_M1_Reg_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_Reg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    Value *cond = ConstantInt::get(i32,instr.args.g4.cond);
    IRB.CreateCall4(fct,proc,m,n,cond);
  } break;
  case SLV6_ADD_M1_Imm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_Imm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ADD_M1_Imm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_Imm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ADD_M1_Reg_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_Reg_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADD_M1_Reg_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_Reg_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_EOR_M1_Reg_S1_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_Reg_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_EOR_M1_Reg_S0_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_Reg_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_AND_M1_Imm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_Imm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_AND_M1_Imm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_Imm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MOV_M1_LSRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g6.cond);
    Value *args[5] = {proc,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_LSRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g6.cond);
    Value *args[5] = {proc,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CPY_ID: {
    Function *fct = module->getFunction("slv6_X_CPY"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g7.d);
    Value *m = ConstantInt::get(i8,instr.args.g7.m);
    Value *cond = ConstantInt::get(i32,instr.args.g7.cond);
    IRB.CreateCall4(fct,proc,d,m,cond);
  } break;
  case SLV6_MOV_M1_LSLImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSLImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g6.cond);
    Value *args[5] = {proc,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_LSLImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSLImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g6.cond);
    Value *args[5] = {proc,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_Imm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_Imm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g8.d);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g8.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g8.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g8.immed_rotated);
    Value *args[5] = {proc,d,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_Imm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_Imm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g8.d);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g8.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g8.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g8.immed_rotated);
    Value *args[5] = {proc,d,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDM1_M4_IA_W1_ID: {
    Function *fct = module->getFunction("slv6_X_LDM1_M4_IA_W1"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDM1_M4_IA_W0_ID: {
    Function *fct = module->getFunction("slv6_X_LDM1_M4_IA_W0"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMP_M1_Imm_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_Imm"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g10.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g10.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g10.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g10.immed_rotated);
    Value *args[5] = {proc,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDR_M2_ScRegOff_U1_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_ScRegOff_U1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g11.cond);
    Value *args[7] = {proc,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_LDR_M2_ScRegOff_U0_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_ScRegOff_U0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g11.cond);
    Value *args[7] = {proc,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_BX_ID: {
    Function *fct = module->getFunction("slv6_X_BX"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g12.m);
    Value *cond = ConstantInt::get(i32,instr.args.g12.cond);
    IRB.CreateCall3(fct,proc,m,cond);
  } break;
  case SLV6_ADD_M1_LSLImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_LSLImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ADD_M1_LSLImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_LSLImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRB_M2_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_ImmOff"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_Reg_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_Reg_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_Reg_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_Reg_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_RRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_RRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g6.cond);
    Value *args[5] = {proc,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_RRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_RRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g6.cond);
    Value *args[5] = {proc,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDR_M2_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_Imm_postInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_EOR_M1_RRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_RRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_EOR_M1_RRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_RRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_AND_M1_Reg_S1_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_Reg_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_AND_M1_Reg_S0_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_Reg_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STR_M2_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_Imm_preInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STRB_M2_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_ImmOff"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_LSLImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_LSLImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ORR_M1_LSLImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_LSLImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ADC_M1_Reg_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_Reg_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADC_M1_Reg_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_Reg_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDRB_M2_RegOff_U1_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_RegOff_U1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDRB_M2_RegOff_U0_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_RegOff_U0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_RSB_M1_Reg_S1_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_Reg_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_RSB_M1_Reg_S0_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_Reg_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_BIC_M1_Imm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_Imm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_BIC_M1_Imm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_Imm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MVN_M1_Imm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_Imm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g8.d);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g8.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g8.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g8.immed_rotated);
    Value *args[5] = {proc,d,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MVN_M1_Imm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_Imm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g8.d);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g8.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g8.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g8.immed_rotated);
    Value *args[5] = {proc,d,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_LSRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_LSRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ORR_M1_LSRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_LSRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_EOR_M1_LSRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_LSRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_EOR_M1_LSRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_LSRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDR_M2_RegOff_U1_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_RegOff_U1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDR_M2_RegOff_U0_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_RegOff_U0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_LSRReg_S1_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSRReg_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    Value *cond = ConstantInt::get(i32,instr.args.g14.cond);
    Value *args[5] = {proc,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_LSRReg_S0_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSRReg_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    Value *cond = ConstantInt::get(i32,instr.args.g14.cond);
    Value *args[5] = {proc,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STRB_M2_RegOff_U1_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_RegOff_U1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STRB_M2_RegOff_U0_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_RegOff_U0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STR_M2_ScRegOff_U1_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_ScRegOff_U1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g11.cond);
    Value *args[7] = {proc,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_STR_M2_ScRegOff_U0_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_ScRegOff_U0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g11.cond);
    Value *args[7] = {proc,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_CMN_M1_Reg_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_Reg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    Value *cond = ConstantInt::get(i32,instr.args.g4.cond);
    IRB.CreateCall4(fct,proc,m,n,cond);
  } break;
  case SLV6_STR_M2_Reg_postInd_U1_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_Reg_postInd_U1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STR_M2_Reg_postInd_U0_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_Reg_postInd_U0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STR_M2_RegOff_U1_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_RegOff_U1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STR_M2_RegOff_U0_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_RegOff_U0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_EOR_M1_LSLImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_LSLImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_EOR_M1_LSLImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_LSLImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_RSB_M1_Imm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_Imm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_RSB_M1_Imm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_Imm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MOV_M1_ASRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_ASRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g6.cond);
    Value *args[5] = {proc,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_ASRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_ASRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g6.cond);
    Value *args[5] = {proc,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADD_M1_RRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_RRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ADD_M1_RRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_RRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_RSB_M1_LSLImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_LSLImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_RSB_M1_LSLImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_LSLImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRB_M2_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_Imm_postInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STM1_M4_IA_W1_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_IA_W1"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STM1_M4_IA_W0_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_IA_W0"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TST_M1_Imm_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_Imm"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g10.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g10.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g10.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g10.immed_rotated);
    Value *args[5] = {proc,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STM1_M4_DB_W1_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_DB_W1"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STM1_M4_DB_W0_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_DB_W0"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MVN_M1_Reg_S1_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_Reg_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g7.d);
    Value *m = ConstantInt::get(i8,instr.args.g7.m);
    Value *cond = ConstantInt::get(i32,instr.args.g7.cond);
    IRB.CreateCall4(fct,proc,d,m,cond);
  } break;
  case SLV6_MVN_M1_Reg_S0_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_Reg_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g7.d);
    Value *m = ConstantInt::get(i8,instr.args.g7.m);
    Value *cond = ConstantInt::get(i32,instr.args.g7.cond);
    IRB.CreateCall4(fct,proc,d,m,cond);
  } break;
  case SLV6_STM1_M4_IB_W1_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_IB_W1"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STM1_M4_IB_W0_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_IB_W0"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADD_M1_LSRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_LSRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ADD_M1_LSRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_LSRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STR_M2_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_Imm_postInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDRB_M2_ScRegOff_U1_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_ScRegOff_U1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g11.cond);
    Value *args[7] = {proc,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_LDRB_M2_ScRegOff_U0_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_ScRegOff_U0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g11.cond);
    Value *args[7] = {proc,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SUB_M1_LSLImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_LSLImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SUB_M1_LSLImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_LSLImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDM1_M4_IB_W1_ID: {
    Function *fct = module->getFunction("slv6_X_LDM1_M4_IB_W1"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDM1_M4_IB_W0_ID: {
    Function *fct = module->getFunction("slv6_X_LDM1_M4_IB_W0"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDRH_M3_ImmOff_U1_ID: {
    Function *fct = module->getFunction("slv6_X_LDRH_M3_ImmOff_U1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g15.d);
    Value *n = ConstantInt::get(i8,instr.args.g15.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g15.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g15.cond);
    Value *args[5] = {proc,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDRH_M3_ImmOff_U0_ID: {
    Function *fct = module->getFunction("slv6_X_LDRH_M3_ImmOff_U0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g15.d);
    Value *n = ConstantInt::get(i8,instr.args.g15.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g15.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g15.cond);
    Value *args[5] = {proc,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDR_M2_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_Imm_preInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SMULL_S1_ID: {
    Function *fct = module->getFunction("slv6_X_SMULL_S1"); assert(fct);
    Value *dHi = ConstantInt::get(i8,instr.args.g16.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g16.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g16.m);
    Value *s = ConstantInt::get(i8,instr.args.g16.s);
    Value *cond = ConstantInt::get(i32,instr.args.g16.cond);
    Value *args[6] = {proc,dHi,dLo,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SMULL_S0_ID: {
    Function *fct = module->getFunction("slv6_X_SMULL_S0"); assert(fct);
    Value *dHi = ConstantInt::get(i8,instr.args.g16.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g16.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g16.m);
    Value *s = ConstantInt::get(i8,instr.args.g16.s);
    Value *cond = ConstantInt::get(i32,instr.args.g16.cond);
    Value *args[6] = {proc,dHi,dLo,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_RSB_M1_ASRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_ASRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_RSB_M1_ASRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_ASRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_TST_M1_Reg_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_Reg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    Value *cond = ConstantInt::get(i32,instr.args.g4.cond);
    IRB.CreateCall4(fct,proc,m,n,cond);
  } break;
  case SLV6_EOR_M1_Imm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_Imm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_EOR_M1_Imm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_Imm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ORR_M1_ASRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_ASRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ORR_M1_ASRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_ASRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ORR_M1_Imm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_Imm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ORR_M1_Imm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_Imm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g3.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[6] = {proc,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SUB_M1_ASRImm_S1_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_ASRImm_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SUB_M1_ASRImm_S0_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_ASRImm_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MOV_M1_LSLReg_S1_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSLReg_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    Value *cond = ConstantInt::get(i32,instr.args.g14.cond);
    Value *args[5] = {proc,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_LSLReg_S0_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSLReg_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    Value *cond = ConstantInt::get(i32,instr.args.g14.cond);
    Value *args[5] = {proc,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MUL_S1_ID: {
    Function *fct = module->getFunction("slv6_X_MUL_S1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    Value *cond = ConstantInt::get(i32,instr.args.g14.cond);
    Value *args[5] = {proc,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MUL_S0_ID: {
    Function *fct = module->getFunction("slv6_X_MUL_S0"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    Value *cond = ConstantInt::get(i32,instr.args.g14.cond);
    Value *args[5] = {proc,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMN_M1_Imm_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_Imm"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g10.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g10.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g10.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g10.immed_rotated);
    Value *args[5] = {proc,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADC_M1_Imm_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_Imm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g17.S);
    Value *d = ConstantInt::get(i8,instr.args.g17.d);
    Value *n = ConstantInt::get(i8,instr.args.g17.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g17.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g17.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g17.immed_rotated);
    Value *args[7] = {proc,S,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADC_M1_LSLImm_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_LSLImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADC_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADC_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_LSRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADC_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADC_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_ASRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADC_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADC_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_RRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADC_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADC_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_ADD_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADD_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADD_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_ASRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADD_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADD_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ADD_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_AND_M1_LSLImm_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_LSLImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_AND_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_AND_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_LSRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_AND_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_AND_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_ASRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_AND_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_AND_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_RRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_AND_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_AND_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_BIC_M1_Reg_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_Reg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_BIC_M1_LSLImm_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_LSLImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_BIC_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_BIC_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_LSRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_BIC_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_BIC_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_ASRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_BIC_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_BIC_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_RRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_BIC_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_BIC_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_BKPT_ID: {
    Function *fct = module->getFunction("slv6_X_BKPT"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_BLX1_ID: {
    Function *fct = module->getFunction("slv6_X_BLX1"); assert(fct);
    Value *pc_offset_h = ConstantInt::get(i32,instr.args.g21.pc_offset_h);
    IRB.CreateCall2(fct,proc,pc_offset_h);
  } break;
  case SLV6_BLX2_ID: {
    Function *fct = module->getFunction("slv6_X_BLX2"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g12.m);
    Value *cond = ConstantInt::get(i32,instr.args.g12.cond);
    IRB.CreateCall3(fct,proc,m,cond);
  } break;
  case SLV6_BXJ_ID: {
    Function *fct = module->getFunction("slv6_X_BXJ"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g12.m);
    Value *cond = ConstantInt::get(i32,instr.args.g12.cond);
    IRB.CreateCall3(fct,proc,m,cond);
  } break;
  case SLV6_CDP_ID: {
    Function *fct = module->getFunction("slv6_X_CDP"); assert(fct);
    Value *cp_num = ConstantInt::get(i8,instr.args.g22.cp_num);
    Value *cond = ConstantInt::get(i32,instr.args.g22.cond);
    IRB.CreateCall3(fct,proc,cp_num,cond);
  } break;
  case SLV6_CLZ_ID: {
    Function *fct = module->getFunction("slv6_X_CLZ"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g7.d);
    Value *m = ConstantInt::get(i8,instr.args.g7.m);
    Value *cond = ConstantInt::get(i32,instr.args.g7.cond);
    IRB.CreateCall4(fct,proc,d,m,cond);
  } break;
  case SLV6_CMN_M1_LSLImm_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_LSLImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMN_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_LSLReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMN_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_LSRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMN_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_LSRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMN_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_ASRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMN_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_ASRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMN_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_RRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMN_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_RRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMN_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_RRE"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    Value *cond = ConstantInt::get(i32,instr.args.g4.cond);
    IRB.CreateCall4(fct,proc,m,n,cond);
  } break;
  case SLV6_CMP_M1_LSLImm_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_LSLImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMP_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_LSLReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMP_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_LSRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMP_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_LSRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMP_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_ASRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMP_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_ASRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMP_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_RRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMP_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_RRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMP_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_RRE"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    Value *cond = ConstantInt::get(i32,instr.args.g4.cond);
    IRB.CreateCall4(fct,proc,m,n,cond);
  } break;
  case SLV6_CPS_ID: {
    Function *fct = module->getFunction("slv6_X_CPS"); assert(fct);
    Value *A = ConstantInt::get(i8,instr.args.g25.A);
    Value *F = ConstantInt::get(i8,instr.args.g25.F);
    Value *I = ConstantInt::get(i8,instr.args.g25.I);
    Value *imod = ConstantInt::get(i8,instr.args.g25.imod);
    Value *mmod = ConstantInt::get(i8,instr.args.g25.mmod);
    Value *mode = ConstantInt::get(i32,instr.args.g25.mode);
    Value *args[7] = {proc,A,F,I,imod,mmod,mode};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_EOR_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_EOR_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_EOR_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_ASRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_EOR_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_EOR_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_EOR_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDC_M5_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_LDC_M5_ImmOff"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_LDC_M5_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDC_M5_Imm_preInd"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_LDC_M5_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDC_M5_Imm_postInd"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_LDC_M5_U_ID: {
    Function *fct = module->getFunction("slv6_X_LDC_M5_U"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_LDM1_M4_DA_ID: {
    Function *fct = module->getFunction("slv6_X_LDM1_M4_DA"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g26.W);
    Value *n = ConstantInt::get(i8,instr.args.g26.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g26.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g26.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g26.register_list);
    Value *args[6] = {proc,W,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDM1_M4_DB_ID: {
    Function *fct = module->getFunction("slv6_X_LDM1_M4_DB"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g26.W);
    Value *n = ConstantInt::get(i8,instr.args.g26.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g26.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g26.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g26.register_list);
    Value *args[6] = {proc,W,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDM2_M4_IA_ID: {
    Function *fct = module->getFunction("slv6_X_LDM2_M4_IA"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDM2_M4_IB_ID: {
    Function *fct = module->getFunction("slv6_X_LDM2_M4_IB"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDM2_M4_DA_ID: {
    Function *fct = module->getFunction("slv6_X_LDM2_M4_DA"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDM2_M4_DB_ID: {
    Function *fct = module->getFunction("slv6_X_LDM2_M4_DB"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDM3_M4_IA_ID: {
    Function *fct = module->getFunction("slv6_X_LDM3_M4_IA"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g26.W);
    Value *n = ConstantInt::get(i8,instr.args.g26.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g26.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g26.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g26.register_list);
    Value *args[6] = {proc,W,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDM3_M4_IB_ID: {
    Function *fct = module->getFunction("slv6_X_LDM3_M4_IB"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g26.W);
    Value *n = ConstantInt::get(i8,instr.args.g26.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g26.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g26.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g26.register_list);
    Value *args[6] = {proc,W,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDM3_M4_DA_ID: {
    Function *fct = module->getFunction("slv6_X_LDM3_M4_DA"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g26.W);
    Value *n = ConstantInt::get(i8,instr.args.g26.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g26.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g26.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g26.register_list);
    Value *args[6] = {proc,W,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDM3_M4_DB_ID: {
    Function *fct = module->getFunction("slv6_X_LDM3_M4_DB"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g26.W);
    Value *n = ConstantInt::get(i8,instr.args.g26.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g26.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g26.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g26.register_list);
    Value *args[6] = {proc,W,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDR_M2_Reg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_Reg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDR_M2_ScReg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_ScReg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_LDR_M2_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDR_M2_ScReg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_ScReg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_LDRB_M2_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_Imm_preInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDRB_M2_Reg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_Reg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRB_M2_ScReg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_ScReg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_LDRB_M2_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_Imm_postInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDRB_M2_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRB_M2_ScReg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_ScReg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_LDRBT_M2_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRBT_M2_Imm_postInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDRBT_M2_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRBT_M2_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRBT_M2_ScReg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRBT_M2_ScReg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_LDRD_M3_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_LDRD_M3_ImmOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRD_M3_RegOff_ID: {
    Function *fct = module->getFunction("slv6_X_LDRD_M3_RegOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRD_M3_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRD_M3_Imm_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRD_M3_Reg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRD_M3_Reg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRD_M3_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRD_M3_Imm_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRD_M3_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRD_M3_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDREX_ID: {
    Function *fct = module->getFunction("slv6_X_LDREX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g30.d);
    Value *n = ConstantInt::get(i8,instr.args.g30.n);
    Value *cond = ConstantInt::get(i32,instr.args.g30.cond);
    IRB.CreateCall4(fct,proc,d,n,cond);
  } break;
  case SLV6_LDRH_M3_RegOff_ID: {
    Function *fct = module->getFunction("slv6_X_LDRH_M3_RegOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRH_M3_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRH_M3_Imm_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRH_M3_Reg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRH_M3_Reg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRH_M3_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRH_M3_Imm_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRH_M3_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRH_M3_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSB_M3_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSB_M3_ImmOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSB_M3_RegOff_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSB_M3_RegOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSB_M3_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSB_M3_Imm_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSB_M3_Reg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSB_M3_Reg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSB_M3_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSB_M3_Imm_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSB_M3_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSB_M3_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSH_M3_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSH_M3_ImmOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSH_M3_RegOff_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSH_M3_RegOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSH_M3_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSH_M3_Imm_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSH_M3_Reg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSH_M3_Reg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSH_M3_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSH_M3_Imm_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRSH_M3_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRSH_M3_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRT_M2_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRT_M2_Imm_postInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDRT_M2_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRT_M2_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRT_M2_ScReg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_LDRT_M2_ScReg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_MCR_ID: {
    Function *fct = module->getFunction("slv6_X_MCR"); assert(fct);
    Value *CRm = ConstantInt::get(i8,instr.args.g31.CRm);
    Value *CRn = ConstantInt::get(i8,instr.args.g31.CRn);
    Value *cp_num = ConstantInt::get(i8,instr.args.g31.cp_num);
    Value *d = ConstantInt::get(i8,instr.args.g31.d);
    Value *opcode_1 = ConstantInt::get(i8,instr.args.g31.opcode_1);
    Value *opcode_2 = ConstantInt::get(i8,instr.args.g31.opcode_2);
    Value *cond = ConstantInt::get(i32,instr.args.g31.cond);
    Value *args[8] = {proc,CRm,CRn,cp_num,d,opcode_1,opcode_2,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_MCRR_ID: {
    Function *fct = module->getFunction("slv6_X_MCRR"); assert(fct);
    Value *cp_num = ConstantInt::get(i8,instr.args.g32.cp_num);
    Value *d = ConstantInt::get(i8,instr.args.g32.d);
    Value *n = ConstantInt::get(i8,instr.args.g32.n);
    Value *cond = ConstantInt::get(i32,instr.args.g32.cond);
    Value *args[5] = {proc,cp_num,d,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MLA_ID: {
    Function *fct = module->getFunction("slv6_X_MLA"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_MOV_M1_Reg_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_Reg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g33.S);
    Value *d = ConstantInt::get(i8,instr.args.g33.d);
    Value *m = ConstantInt::get(i8,instr.args.g33.m);
    Value *cond = ConstantInt::get(i32,instr.args.g33.cond);
    Value *args[5] = {proc,S,d,m,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g34.S);
    Value *d = ConstantInt::get(i8,instr.args.g34.d);
    Value *m = ConstantInt::get(i8,instr.args.g34.m);
    Value *s = ConstantInt::get(i8,instr.args.g34.s);
    Value *cond = ConstantInt::get(i32,instr.args.g34.cond);
    Value *args[6] = {proc,S,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MOV_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g34.S);
    Value *d = ConstantInt::get(i8,instr.args.g34.d);
    Value *m = ConstantInt::get(i8,instr.args.g34.m);
    Value *s = ConstantInt::get(i8,instr.args.g34.s);
    Value *cond = ConstantInt::get(i32,instr.args.g34.cond);
    Value *args[6] = {proc,S,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MOV_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g33.S);
    Value *d = ConstantInt::get(i8,instr.args.g33.d);
    Value *m = ConstantInt::get(i8,instr.args.g33.m);
    Value *cond = ConstantInt::get(i32,instr.args.g33.cond);
    Value *args[5] = {proc,S,d,m,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MRC_ID: {
    Function *fct = module->getFunction("slv6_X_MRC"); assert(fct);
    Value *CRm = ConstantInt::get(i8,instr.args.g31.CRm);
    Value *CRn = ConstantInt::get(i8,instr.args.g31.CRn);
    Value *cp_num = ConstantInt::get(i8,instr.args.g31.cp_num);
    Value *d = ConstantInt::get(i8,instr.args.g31.d);
    Value *opcode_1 = ConstantInt::get(i8,instr.args.g31.opcode_1);
    Value *opcode_2 = ConstantInt::get(i8,instr.args.g31.opcode_2);
    Value *cond = ConstantInt::get(i32,instr.args.g31.cond);
    Value *args[8] = {proc,CRm,CRn,cp_num,d,opcode_1,opcode_2,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_MRRC_ID: {
    Function *fct = module->getFunction("slv6_X_MRRC"); assert(fct);
    Value *cp_num = ConstantInt::get(i8,instr.args.g32.cp_num);
    Value *d = ConstantInt::get(i8,instr.args.g32.d);
    Value *n = ConstantInt::get(i8,instr.args.g32.n);
    Value *cond = ConstantInt::get(i32,instr.args.g32.cond);
    Value *args[5] = {proc,cp_num,d,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MRS_ID: {
    Function *fct = module->getFunction("slv6_X_MRS"); assert(fct);
    Value *R = ConstantInt::get(i8,instr.args.g35.R);
    Value *d = ConstantInt::get(i8,instr.args.g35.d);
    Value *cond = ConstantInt::get(i32,instr.args.g35.cond);
    IRB.CreateCall4(fct,proc,R,d,cond);
  } break;
  case SLV6_MSRimm_ID: {
    Function *fct = module->getFunction("slv6_X_MSRimm"); assert(fct);
    Value *R = ConstantInt::get(i8,instr.args.g36.R);
    Value *field_mask = ConstantInt::get(i8,instr.args.g36.field_mask);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g36.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g36.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g36.immed_rotated);
    Value *args[6] = {proc,R,field_mask,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MSRreg_ID: {
    Function *fct = module->getFunction("slv6_X_MSRreg"); assert(fct);
    Value *R = ConstantInt::get(i8,instr.args.g37.R);
    Value *field_mask = ConstantInt::get(i8,instr.args.g37.field_mask);
    Value *m = ConstantInt::get(i8,instr.args.g37.m);
    Value *cond = ConstantInt::get(i32,instr.args.g37.cond);
    Value *args[5] = {proc,R,field_mask,m,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MVN_M1_LSLImm_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_LSLImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g38.S);
    Value *d = ConstantInt::get(i8,instr.args.g38.d);
    Value *m = ConstantInt::get(i8,instr.args.g38.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g38.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g38.cond);
    Value *args[6] = {proc,S,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MVN_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g34.S);
    Value *d = ConstantInt::get(i8,instr.args.g34.d);
    Value *m = ConstantInt::get(i8,instr.args.g34.m);
    Value *s = ConstantInt::get(i8,instr.args.g34.s);
    Value *cond = ConstantInt::get(i32,instr.args.g34.cond);
    Value *args[6] = {proc,S,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MVN_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_LSRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g38.S);
    Value *d = ConstantInt::get(i8,instr.args.g38.d);
    Value *m = ConstantInt::get(i8,instr.args.g38.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g38.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g38.cond);
    Value *args[6] = {proc,S,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MVN_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g34.S);
    Value *d = ConstantInt::get(i8,instr.args.g34.d);
    Value *m = ConstantInt::get(i8,instr.args.g34.m);
    Value *s = ConstantInt::get(i8,instr.args.g34.s);
    Value *cond = ConstantInt::get(i32,instr.args.g34.cond);
    Value *args[6] = {proc,S,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MVN_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_ASRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g38.S);
    Value *d = ConstantInt::get(i8,instr.args.g38.d);
    Value *m = ConstantInt::get(i8,instr.args.g38.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g38.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g38.cond);
    Value *args[6] = {proc,S,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MVN_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g34.S);
    Value *d = ConstantInt::get(i8,instr.args.g34.d);
    Value *m = ConstantInt::get(i8,instr.args.g34.m);
    Value *s = ConstantInt::get(i8,instr.args.g34.s);
    Value *cond = ConstantInt::get(i32,instr.args.g34.cond);
    Value *args[6] = {proc,S,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MVN_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_RRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g38.S);
    Value *d = ConstantInt::get(i8,instr.args.g38.d);
    Value *m = ConstantInt::get(i8,instr.args.g38.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g38.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g38.cond);
    Value *args[6] = {proc,S,d,m,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MVN_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g34.S);
    Value *d = ConstantInt::get(i8,instr.args.g34.d);
    Value *m = ConstantInt::get(i8,instr.args.g34.m);
    Value *s = ConstantInt::get(i8,instr.args.g34.s);
    Value *cond = ConstantInt::get(i32,instr.args.g34.cond);
    Value *args[6] = {proc,S,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_MVN_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g33.S);
    Value *d = ConstantInt::get(i8,instr.args.g33.d);
    Value *m = ConstantInt::get(i8,instr.args.g33.m);
    Value *cond = ConstantInt::get(i32,instr.args.g33.cond);
    Value *args[5] = {proc,S,d,m,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ORR_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ORR_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ORR_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_RRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ORR_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_ORR_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_PKHBT_ID: {
    Function *fct = module->getFunction("slv6_X_PKHBT"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_PKHTB_ID: {
    Function *fct = module->getFunction("slv6_X_PKHTB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g13.cond);
    Value *args[6] = {proc,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_PLD_M2_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_PLD_M2_ImmOff"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g39.n);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g39.signed_offset_12);
    IRB.CreateCall3(fct,proc,n,signed_offset_12);
  } break;
  case SLV6_PLD_M2_RegOff_ID: {
    Function *fct = module->getFunction("slv6_X_PLD_M2_RegOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g40.U);
    Value *m = ConstantInt::get(i8,instr.args.g40.m);
    Value *n = ConstantInt::get(i8,instr.args.g40.n);
    IRB.CreateCall4(fct,proc,U,m,n);
  } break;
  case SLV6_PLD_M2_ScRegOff_ID: {
    Function *fct = module->getFunction("slv6_X_PLD_M2_ScRegOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g41.U);
    Value *m = ConstantInt::get(i8,instr.args.g41.m);
    Value *n = ConstantInt::get(i8,instr.args.g41.n);
    Value *shift = ConstantInt::get(i8,instr.args.g41.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g41.shift_imm);
    Value *args[6] = {proc,U,m,n,shift,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_QADD_ID: {
    Function *fct = module->getFunction("slv6_X_QADD"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_QADD16_ID: {
    Function *fct = module->getFunction("slv6_X_QADD16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_QADD8_ID: {
    Function *fct = module->getFunction("slv6_X_QADD8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_QADDSUBX_ID: {
    Function *fct = module->getFunction("slv6_X_QADDSUBX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_QDADD_ID: {
    Function *fct = module->getFunction("slv6_X_QDADD"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_QDSUB_ID: {
    Function *fct = module->getFunction("slv6_X_QDSUB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_QSUB_ID: {
    Function *fct = module->getFunction("slv6_X_QSUB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_QSUB16_ID: {
    Function *fct = module->getFunction("slv6_X_QSUB16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_QSUB8_ID: {
    Function *fct = module->getFunction("slv6_X_QSUB8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_QSUBADDX_ID: {
    Function *fct = module->getFunction("slv6_X_QSUBADDX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_REV_ID: {
    Function *fct = module->getFunction("slv6_X_REV"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g7.d);
    Value *m = ConstantInt::get(i8,instr.args.g7.m);
    Value *cond = ConstantInt::get(i32,instr.args.g7.cond);
    IRB.CreateCall4(fct,proc,d,m,cond);
  } break;
  case SLV6_REV16_ID: {
    Function *fct = module->getFunction("slv6_X_REV16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g7.d);
    Value *m = ConstantInt::get(i8,instr.args.g7.m);
    Value *cond = ConstantInt::get(i32,instr.args.g7.cond);
    IRB.CreateCall4(fct,proc,d,m,cond);
  } break;
  case SLV6_REVSH_ID: {
    Function *fct = module->getFunction("slv6_X_REVSH"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g7.d);
    Value *m = ConstantInt::get(i8,instr.args.g7.m);
    Value *cond = ConstantInt::get(i32,instr.args.g7.cond);
    IRB.CreateCall4(fct,proc,d,m,cond);
  } break;
  case SLV6_RFE_M4_IA_ID: {
    Function *fct = module->getFunction("slv6_X_RFE_M4_IA"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g42.W);
    Value *n = ConstantInt::get(i8,instr.args.g42.n);
    IRB.CreateCall3(fct,proc,W,n);
  } break;
  case SLV6_RFE_M4_IB_ID: {
    Function *fct = module->getFunction("slv6_X_RFE_M4_IB"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g42.W);
    Value *n = ConstantInt::get(i8,instr.args.g42.n);
    IRB.CreateCall3(fct,proc,W,n);
  } break;
  case SLV6_RFE_M4_DA_ID: {
    Function *fct = module->getFunction("slv6_X_RFE_M4_DA"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g42.W);
    Value *n = ConstantInt::get(i8,instr.args.g42.n);
    IRB.CreateCall3(fct,proc,W,n);
  } break;
  case SLV6_RFE_M4_DB_ID: {
    Function *fct = module->getFunction("slv6_X_RFE_M4_DB"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g42.W);
    Value *n = ConstantInt::get(i8,instr.args.g42.n);
    IRB.CreateCall3(fct,proc,W,n);
  } break;
  case SLV6_RSB_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSB_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_LSRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSB_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSB_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSB_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_RRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSB_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSB_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_RSC_M1_Imm_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_Imm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g17.S);
    Value *d = ConstantInt::get(i8,instr.args.g17.d);
    Value *n = ConstantInt::get(i8,instr.args.g17.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g17.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g17.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g17.immed_rotated);
    Value *args[7] = {proc,S,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSC_M1_Reg_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_Reg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_RSC_M1_LSLImm_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_LSLImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSC_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSC_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_LSRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSC_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSC_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_ASRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSC_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSC_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_RRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSC_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_RSC_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_RSC_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SADD16_ID: {
    Function *fct = module->getFunction("slv6_X_SADD16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SADD8_ID: {
    Function *fct = module->getFunction("slv6_X_SADD8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SADDSUBX_ID: {
    Function *fct = module->getFunction("slv6_X_SADDSUBX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SBC_M1_Imm_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_Imm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g17.S);
    Value *d = ConstantInt::get(i8,instr.args.g17.d);
    Value *n = ConstantInt::get(i8,instr.args.g17.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g17.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g17.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g17.immed_rotated);
    Value *args[7] = {proc,S,d,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SBC_M1_Reg_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_Reg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SBC_M1_LSLImm_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_LSLImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SBC_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SBC_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_LSRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SBC_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SBC_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_ASRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SBC_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SBC_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_RRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SBC_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SBC_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_SBC_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SEL_ID: {
    Function *fct = module->getFunction("slv6_X_SEL"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SETEND_ID: {
    Function *fct = module->getFunction("slv6_X_SETEND"); assert(fct);
    Value *E = ConstantInt::get(i8,instr.args.g43.E);
    IRB.CreateCall2(fct,proc,E);
  } break;
  case SLV6_SHADD16_ID: {
    Function *fct = module->getFunction("slv6_X_SHADD16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SHADD8_ID: {
    Function *fct = module->getFunction("slv6_X_SHADD8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SHADDSUBX_ID: {
    Function *fct = module->getFunction("slv6_X_SHADDSUBX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SHSUB16_ID: {
    Function *fct = module->getFunction("slv6_X_SHSUB16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SHSUB8_ID: {
    Function *fct = module->getFunction("slv6_X_SHSUB8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SHSUBADDX_ID: {
    Function *fct = module->getFunction("slv6_X_SHSUBADDX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SMLAxy_ID: {
    Function *fct = module->getFunction("slv6_X_SMLAxy"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g44.d);
    Value *m = ConstantInt::get(i8,instr.args.g44.m);
    Value *n = ConstantInt::get(i8,instr.args.g44.n);
    Value *s = ConstantInt::get(i8,instr.args.g44.s);
    Value *x = ConstantInt::get(i8,instr.args.g44.x);
    Value *y = ConstantInt::get(i8,instr.args.g44.y);
    Value *cond = ConstantInt::get(i32,instr.args.g44.cond);
    Value *args[8] = {proc,d,m,n,s,x,y,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_SMLAD_ID: {
    Function *fct = module->getFunction("slv6_X_SMLAD"); assert(fct);
    Value *X = ConstantInt::get(i8,instr.args.g45.X);
    Value *d = ConstantInt::get(i8,instr.args.g45.d);
    Value *m = ConstantInt::get(i8,instr.args.g45.m);
    Value *n = ConstantInt::get(i8,instr.args.g45.n);
    Value *s = ConstantInt::get(i8,instr.args.g45.s);
    Value *cond = ConstantInt::get(i32,instr.args.g45.cond);
    Value *args[7] = {proc,X,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SMLAL_ID: {
    Function *fct = module->getFunction("slv6_X_SMLAL"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g46.S);
    Value *dHi = ConstantInt::get(i8,instr.args.g46.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g46.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g46.m);
    Value *s = ConstantInt::get(i8,instr.args.g46.s);
    Value *cond = ConstantInt::get(i32,instr.args.g46.cond);
    Value *args[7] = {proc,S,dHi,dLo,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SMLALxy_ID: {
    Function *fct = module->getFunction("slv6_X_SMLALxy"); assert(fct);
    Value *dHi = ConstantInt::get(i8,instr.args.g47.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g47.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g47.m);
    Value *s = ConstantInt::get(i8,instr.args.g47.s);
    Value *x = ConstantInt::get(i8,instr.args.g47.x);
    Value *y = ConstantInt::get(i8,instr.args.g47.y);
    Value *cond = ConstantInt::get(i32,instr.args.g47.cond);
    Value *args[8] = {proc,dHi,dLo,m,s,x,y,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_SMLALD_ID: {
    Function *fct = module->getFunction("slv6_X_SMLALD"); assert(fct);
    Value *X = ConstantInt::get(i8,instr.args.g48.X);
    Value *dHi = ConstantInt::get(i8,instr.args.g48.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g48.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g48.m);
    Value *s = ConstantInt::get(i8,instr.args.g48.s);
    Value *cond = ConstantInt::get(i32,instr.args.g48.cond);
    Value *args[7] = {proc,X,dHi,dLo,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SMLAWy_ID: {
    Function *fct = module->getFunction("slv6_X_SMLAWy"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g49.d);
    Value *m = ConstantInt::get(i8,instr.args.g49.m);
    Value *n = ConstantInt::get(i8,instr.args.g49.n);
    Value *s = ConstantInt::get(i8,instr.args.g49.s);
    Value *y = ConstantInt::get(i8,instr.args.g49.y);
    Value *cond = ConstantInt::get(i32,instr.args.g49.cond);
    Value *args[7] = {proc,d,m,n,s,y,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SMLSD_ID: {
    Function *fct = module->getFunction("slv6_X_SMLSD"); assert(fct);
    Value *X = ConstantInt::get(i8,instr.args.g45.X);
    Value *d = ConstantInt::get(i8,instr.args.g45.d);
    Value *m = ConstantInt::get(i8,instr.args.g45.m);
    Value *n = ConstantInt::get(i8,instr.args.g45.n);
    Value *s = ConstantInt::get(i8,instr.args.g45.s);
    Value *cond = ConstantInt::get(i32,instr.args.g45.cond);
    Value *args[7] = {proc,X,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SMLSLD_ID: {
    Function *fct = module->getFunction("slv6_X_SMLSLD"); assert(fct);
    Value *X = ConstantInt::get(i8,instr.args.g48.X);
    Value *dHi = ConstantInt::get(i8,instr.args.g48.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g48.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g48.m);
    Value *s = ConstantInt::get(i8,instr.args.g48.s);
    Value *cond = ConstantInt::get(i32,instr.args.g48.cond);
    Value *args[7] = {proc,X,dHi,dLo,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SMMLA_ID: {
    Function *fct = module->getFunction("slv6_X_SMMLA"); assert(fct);
    Value *R = ConstantInt::get(i8,instr.args.g50.R);
    Value *d = ConstantInt::get(i8,instr.args.g50.d);
    Value *m = ConstantInt::get(i8,instr.args.g50.m);
    Value *n = ConstantInt::get(i8,instr.args.g50.n);
    Value *s = ConstantInt::get(i8,instr.args.g50.s);
    Value *cond = ConstantInt::get(i32,instr.args.g50.cond);
    Value *args[7] = {proc,R,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SMMLS_ID: {
    Function *fct = module->getFunction("slv6_X_SMMLS"); assert(fct);
    Value *R = ConstantInt::get(i8,instr.args.g50.R);
    Value *d = ConstantInt::get(i8,instr.args.g50.d);
    Value *m = ConstantInt::get(i8,instr.args.g50.m);
    Value *n = ConstantInt::get(i8,instr.args.g50.n);
    Value *s = ConstantInt::get(i8,instr.args.g50.s);
    Value *cond = ConstantInt::get(i32,instr.args.g50.cond);
    Value *args[7] = {proc,R,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SMMUL_ID: {
    Function *fct = module->getFunction("slv6_X_SMMUL"); assert(fct);
    Value *R = ConstantInt::get(i8,instr.args.g51.R);
    Value *d = ConstantInt::get(i8,instr.args.g51.d);
    Value *m = ConstantInt::get(i8,instr.args.g51.m);
    Value *s = ConstantInt::get(i8,instr.args.g51.s);
    Value *cond = ConstantInt::get(i32,instr.args.g51.cond);
    Value *args[6] = {proc,R,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SMUAD_ID: {
    Function *fct = module->getFunction("slv6_X_SMUAD"); assert(fct);
    Value *X = ConstantInt::get(i8,instr.args.g52.X);
    Value *d = ConstantInt::get(i8,instr.args.g52.d);
    Value *m = ConstantInt::get(i8,instr.args.g52.m);
    Value *s = ConstantInt::get(i8,instr.args.g52.s);
    Value *cond = ConstantInt::get(i32,instr.args.g52.cond);
    Value *args[6] = {proc,X,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SMULxy_ID: {
    Function *fct = module->getFunction("slv6_X_SMULxy"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g53.d);
    Value *m = ConstantInt::get(i8,instr.args.g53.m);
    Value *s = ConstantInt::get(i8,instr.args.g53.s);
    Value *x = ConstantInt::get(i8,instr.args.g53.x);
    Value *y = ConstantInt::get(i8,instr.args.g53.y);
    Value *cond = ConstantInt::get(i32,instr.args.g53.cond);
    Value *args[7] = {proc,d,m,s,x,y,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SMULWy_ID: {
    Function *fct = module->getFunction("slv6_X_SMULWy"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g54.d);
    Value *m = ConstantInt::get(i8,instr.args.g54.m);
    Value *s = ConstantInt::get(i8,instr.args.g54.s);
    Value *y = ConstantInt::get(i8,instr.args.g54.y);
    Value *cond = ConstantInt::get(i32,instr.args.g54.cond);
    Value *args[6] = {proc,d,m,s,y,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SMUSD_ID: {
    Function *fct = module->getFunction("slv6_X_SMUSD"); assert(fct);
    Value *X = ConstantInt::get(i8,instr.args.g52.X);
    Value *d = ConstantInt::get(i8,instr.args.g52.d);
    Value *m = ConstantInt::get(i8,instr.args.g52.m);
    Value *s = ConstantInt::get(i8,instr.args.g52.s);
    Value *cond = ConstantInt::get(i32,instr.args.g52.cond);
    Value *args[6] = {proc,X,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SRS_M4_IA_ID: {
    Function *fct = module->getFunction("slv6_X_SRS_M4_IA"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g55.W);
    Value *mode = ConstantInt::get(i32,instr.args.g55.mode);
    IRB.CreateCall3(fct,proc,W,mode);
  } break;
  case SLV6_SRS_M4_IB_ID: {
    Function *fct = module->getFunction("slv6_X_SRS_M4_IB"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g55.W);
    Value *mode = ConstantInt::get(i32,instr.args.g55.mode);
    IRB.CreateCall3(fct,proc,W,mode);
  } break;
  case SLV6_SRS_M4_DA_ID: {
    Function *fct = module->getFunction("slv6_X_SRS_M4_DA"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g55.W);
    Value *mode = ConstantInt::get(i32,instr.args.g55.mode);
    IRB.CreateCall3(fct,proc,W,mode);
  } break;
  case SLV6_SRS_M4_DB_ID: {
    Function *fct = module->getFunction("slv6_X_SRS_M4_DB"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g55.W);
    Value *mode = ConstantInt::get(i32,instr.args.g55.mode);
    IRB.CreateCall3(fct,proc,W,mode);
  } break;
  case SLV6_SSAT_ID: {
    Function *fct = module->getFunction("slv6_X_SSAT"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g56.d);
    Value *m = ConstantInt::get(i8,instr.args.g56.m);
    Value *sat_imm = ConstantInt::get(i8,instr.args.g56.sat_imm);
    Value *shift = ConstantInt::get(i8,instr.args.g56.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g56.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g56.cond);
    Value *args[7] = {proc,d,m,sat_imm,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SSAT16_ID: {
    Function *fct = module->getFunction("slv6_X_SSAT16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g57.d);
    Value *m = ConstantInt::get(i8,instr.args.g57.m);
    Value *sat_imm = ConstantInt::get(i8,instr.args.g57.sat_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g57.cond);
    Value *args[5] = {proc,d,m,sat_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SSUB16_ID: {
    Function *fct = module->getFunction("slv6_X_SSUB16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SSUB8_ID: {
    Function *fct = module->getFunction("slv6_X_SSUB8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SSUBADDX_ID: {
    Function *fct = module->getFunction("slv6_X_SSUBADDX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STC_M5_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_STC_M5_ImmOff"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_STC_M5_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STC_M5_Imm_preInd"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_STC_M5_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STC_M5_Imm_postInd"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_STC_M5_U_ID: {
    Function *fct = module->getFunction("slv6_X_STC_M5_U"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_STM1_M4_DA_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_DA"); assert(fct);
    Value *W = ConstantInt::get(i8,instr.args.g26.W);
    Value *n = ConstantInt::get(i8,instr.args.g26.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g26.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g26.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g26.register_list);
    Value *args[6] = {proc,W,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STM2_M4_IA_ID: {
    Function *fct = module->getFunction("slv6_X_STM2_M4_IA"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STM2_M4_IB_ID: {
    Function *fct = module->getFunction("slv6_X_STM2_M4_IB"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STM2_M4_DA_ID: {
    Function *fct = module->getFunction("slv6_X_STM2_M4_DA"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STM2_M4_DB_ID: {
    Function *fct = module->getFunction("slv6_X_STM2_M4_DB"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *cond = ConstantInt::get(i32,instr.args.g9.cond);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    Value *args[5] = {proc,n,nb_reg_x4,cond,register_list};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STR_M2_Reg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_Reg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STR_M2_ScReg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_ScReg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_STR_M2_ScReg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_ScReg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_STRB_M2_ScRegOff_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_ScRegOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_STRB_M2_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_Imm_preInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STRB_M2_Reg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_Reg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRB_M2_ScReg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_ScReg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_STRB_M2_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRB_M2_ScReg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_ScReg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_STRBT_M2_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRBT_M2_Imm_postInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STRBT_M2_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRBT_M2_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRBT_M2_ScReg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRBT_M2_ScReg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_STRD_M3_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_STRD_M3_ImmOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRD_M3_RegOff_ID: {
    Function *fct = module->getFunction("slv6_X_STRD_M3_RegOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRD_M3_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRD_M3_Imm_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRD_M3_Reg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRD_M3_Reg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRD_M3_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRD_M3_Imm_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRD_M3_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRD_M3_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STREX_ID: {
    Function *fct = module->getFunction("slv6_X_STREX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STRH_M3_ImmOff_ID: {
    Function *fct = module->getFunction("slv6_X_STRH_M3_ImmOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRH_M3_RegOff_ID: {
    Function *fct = module->getFunction("slv6_X_STRH_M3_RegOff"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRH_M3_Imm_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRH_M3_Imm_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRH_M3_Reg_preInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRH_M3_Reg_preInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRH_M3_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRH_M3_Imm_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g29.U);
    Value *d = ConstantInt::get(i8,instr.args.g29.d);
    Value *n = ConstantInt::get(i8,instr.args.g29.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g29.immedHL);
    Value *cond = ConstantInt::get(i32,instr.args.g29.cond);
    Value *args[6] = {proc,U,d,n,immedHL,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRH_M3_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRH_M3_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRT_M2_Imm_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRT_M2_Imm_postInd"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *cond = ConstantInt::get(i32,instr.args.g1.cond);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    Value *args[5] = {proc,d,n,cond,signed_offset_12};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STRT_M2_Reg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRT_M2_Reg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g27.U);
    Value *d = ConstantInt::get(i8,instr.args.g27.d);
    Value *m = ConstantInt::get(i8,instr.args.g27.m);
    Value *n = ConstantInt::get(i8,instr.args.g27.n);
    Value *cond = ConstantInt::get(i32,instr.args.g27.cond);
    Value *args[6] = {proc,U,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STRT_M2_ScReg_postInd_ID: {
    Function *fct = module->getFunction("slv6_X_STRT_M2_ScReg_postInd"); assert(fct);
    Value *U = ConstantInt::get(i8,instr.args.g28.U);
    Value *d = ConstantInt::get(i8,instr.args.g28.d);
    Value *m = ConstantInt::get(i8,instr.args.g28.m);
    Value *n = ConstantInt::get(i8,instr.args.g28.n);
    Value *shift = ConstantInt::get(i8,instr.args.g28.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g28.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g28.cond);
    Value *args[8] = {proc,U,d,m,n,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+8);
  } break;
  case SLV6_SUB_M1_Reg_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_Reg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SUB_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_LSLReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SUB_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_LSRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SUB_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_LSRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SUB_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_ASRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SUB_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_RRImm"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g18.S);
    Value *d = ConstantInt::get(i8,instr.args.g18.d);
    Value *m = ConstantInt::get(i8,instr.args.g18.m);
    Value *n = ConstantInt::get(i8,instr.args.g18.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g18.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g18.cond);
    Value *args[7] = {proc,S,d,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SUB_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_RRReg"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g19.S);
    Value *d = ConstantInt::get(i8,instr.args.g19.d);
    Value *m = ConstantInt::get(i8,instr.args.g19.m);
    Value *n = ConstantInt::get(i8,instr.args.g19.n);
    Value *s = ConstantInt::get(i8,instr.args.g19.s);
    Value *cond = ConstantInt::get(i32,instr.args.g19.cond);
    Value *args[7] = {proc,S,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_SUB_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_RRE"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g20.S);
    Value *d = ConstantInt::get(i8,instr.args.g20.d);
    Value *m = ConstantInt::get(i8,instr.args.g20.m);
    Value *n = ConstantInt::get(i8,instr.args.g20.n);
    Value *cond = ConstantInt::get(i32,instr.args.g20.cond);
    Value *args[6] = {proc,S,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SWI_ID: {
    Function *fct = module->getFunction("slv6_X_SWI"); assert(fct);
    Value *cond = ConstantInt::get(i32,instr.args.g58.cond);
    IRB.CreateCall2(fct,proc,cond);
  } break;
  case SLV6_SWP_ID: {
    Function *fct = module->getFunction("slv6_X_SWP"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SWPB_ID: {
    Function *fct = module->getFunction("slv6_X_SWPB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SXTAB_ID: {
    Function *fct = module->getFunction("slv6_X_SXTAB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g59.d);
    Value *m = ConstantInt::get(i8,instr.args.g59.m);
    Value *n = ConstantInt::get(i8,instr.args.g59.n);
    Value *rotate = ConstantInt::get(i8,instr.args.g59.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g59.cond);
    Value *args[6] = {proc,d,m,n,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SXTAB16_ID: {
    Function *fct = module->getFunction("slv6_X_SXTAB16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g59.d);
    Value *m = ConstantInt::get(i8,instr.args.g59.m);
    Value *n = ConstantInt::get(i8,instr.args.g59.n);
    Value *rotate = ConstantInt::get(i8,instr.args.g59.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g59.cond);
    Value *args[6] = {proc,d,m,n,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SXTAH_ID: {
    Function *fct = module->getFunction("slv6_X_SXTAH"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g59.d);
    Value *m = ConstantInt::get(i8,instr.args.g59.m);
    Value *n = ConstantInt::get(i8,instr.args.g59.n);
    Value *rotate = ConstantInt::get(i8,instr.args.g59.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g59.cond);
    Value *args[6] = {proc,d,m,n,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SXTB_ID: {
    Function *fct = module->getFunction("slv6_X_SXTB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g60.d);
    Value *m = ConstantInt::get(i8,instr.args.g60.m);
    Value *rotate = ConstantInt::get(i8,instr.args.g60.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g60.cond);
    Value *args[5] = {proc,d,m,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SXTB16_ID: {
    Function *fct = module->getFunction("slv6_X_SXTB16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g60.d);
    Value *m = ConstantInt::get(i8,instr.args.g60.m);
    Value *rotate = ConstantInt::get(i8,instr.args.g60.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g60.cond);
    Value *args[5] = {proc,d,m,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SXTH_ID: {
    Function *fct = module->getFunction("slv6_X_SXTH"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g60.d);
    Value *m = ConstantInt::get(i8,instr.args.g60.m);
    Value *rotate = ConstantInt::get(i8,instr.args.g60.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g60.cond);
    Value *args[5] = {proc,d,m,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TEQ_M1_Imm_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_Imm"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g10.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g10.rotate_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g10.cond);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g10.immed_rotated);
    Value *args[5] = {proc,n,rotate_imm,cond,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TEQ_M1_Reg_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_Reg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    Value *cond = ConstantInt::get(i32,instr.args.g4.cond);
    IRB.CreateCall4(fct,proc,m,n,cond);
  } break;
  case SLV6_TEQ_M1_LSLImm_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_LSLImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TEQ_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_LSLReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TEQ_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_LSRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TEQ_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_LSRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TEQ_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_ASRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TEQ_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_ASRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TEQ_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_RRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TEQ_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_RRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TEQ_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_TEQ_M1_RRE"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    Value *cond = ConstantInt::get(i32,instr.args.g4.cond);
    IRB.CreateCall4(fct,proc,m,n,cond);
  } break;
  case SLV6_TST_M1_LSLImm_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_LSLImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TST_M1_LSLReg_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_LSLReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TST_M1_LSRImm_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_LSRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TST_M1_LSRReg_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_LSRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TST_M1_ASRImm_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_ASRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TST_M1_ASRReg_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_ASRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TST_M1_RRImm_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_RRImm"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g23.m);
    Value *n = ConstantInt::get(i8,instr.args.g23.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g23.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g23.cond);
    Value *args[5] = {proc,m,n,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TST_M1_RRReg_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_RRReg"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g24.m);
    Value *n = ConstantInt::get(i8,instr.args.g24.n);
    Value *s = ConstantInt::get(i8,instr.args.g24.s);
    Value *cond = ConstantInt::get(i32,instr.args.g24.cond);
    Value *args[5] = {proc,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TST_M1_RRE_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_RRE"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    Value *cond = ConstantInt::get(i32,instr.args.g4.cond);
    IRB.CreateCall4(fct,proc,m,n,cond);
  } break;
  case SLV6_UADD16_ID: {
    Function *fct = module->getFunction("slv6_X_UADD16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UADD8_ID: {
    Function *fct = module->getFunction("slv6_X_UADD8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UADDSUBX_ID: {
    Function *fct = module->getFunction("slv6_X_UADDSUBX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UHADD16_ID: {
    Function *fct = module->getFunction("slv6_X_UHADD16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UHADD8_ID: {
    Function *fct = module->getFunction("slv6_X_UHADD8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UHADDSUBX_ID: {
    Function *fct = module->getFunction("slv6_X_UHADDSUBX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UHSUB16_ID: {
    Function *fct = module->getFunction("slv6_X_UHSUB16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UHSUB8_ID: {
    Function *fct = module->getFunction("slv6_X_UHSUB8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UHSUBADDX_ID: {
    Function *fct = module->getFunction("slv6_X_UHSUBADDX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UMAAL_ID: {
    Function *fct = module->getFunction("slv6_X_UMAAL"); assert(fct);
    Value *dHi = ConstantInt::get(i8,instr.args.g16.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g16.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g16.m);
    Value *s = ConstantInt::get(i8,instr.args.g16.s);
    Value *cond = ConstantInt::get(i32,instr.args.g16.cond);
    Value *args[6] = {proc,dHi,dLo,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_UMLAL_ID: {
    Function *fct = module->getFunction("slv6_X_UMLAL"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g46.S);
    Value *dHi = ConstantInt::get(i8,instr.args.g46.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g46.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g46.m);
    Value *s = ConstantInt::get(i8,instr.args.g46.s);
    Value *cond = ConstantInt::get(i32,instr.args.g46.cond);
    Value *args[7] = {proc,S,dHi,dLo,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_UMULL_ID: {
    Function *fct = module->getFunction("slv6_X_UMULL"); assert(fct);
    Value *S = ConstantInt::get(i8,instr.args.g46.S);
    Value *dHi = ConstantInt::get(i8,instr.args.g46.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g46.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g46.m);
    Value *s = ConstantInt::get(i8,instr.args.g46.s);
    Value *cond = ConstantInt::get(i32,instr.args.g46.cond);
    Value *args[7] = {proc,S,dHi,dLo,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_UQADD16_ID: {
    Function *fct = module->getFunction("slv6_X_UQADD16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UQADD8_ID: {
    Function *fct = module->getFunction("slv6_X_UQADD8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UQADDSUBX_ID: {
    Function *fct = module->getFunction("slv6_X_UQADDSUBX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UQSUB16_ID: {
    Function *fct = module->getFunction("slv6_X_UQSUB16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UQSUB8_ID: {
    Function *fct = module->getFunction("slv6_X_UQSUB8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UQSUBADDX_ID: {
    Function *fct = module->getFunction("slv6_X_UQSUBADDX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_USAD8_ID: {
    Function *fct = module->getFunction("slv6_X_USAD8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    Value *cond = ConstantInt::get(i32,instr.args.g14.cond);
    Value *args[5] = {proc,d,m,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_USADA8_ID: {
    Function *fct = module->getFunction("slv6_X_USADA8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g61.d);
    Value *m = ConstantInt::get(i8,instr.args.g61.m);
    Value *n = ConstantInt::get(i8,instr.args.g61.n);
    Value *s = ConstantInt::get(i8,instr.args.g61.s);
    Value *cond = ConstantInt::get(i32,instr.args.g61.cond);
    Value *args[6] = {proc,d,m,n,s,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_USAT_ID: {
    Function *fct = module->getFunction("slv6_X_USAT"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g56.d);
    Value *m = ConstantInt::get(i8,instr.args.g56.m);
    Value *sat_imm = ConstantInt::get(i8,instr.args.g56.sat_imm);
    Value *shift = ConstantInt::get(i8,instr.args.g56.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g56.shift_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g56.cond);
    Value *args[7] = {proc,d,m,sat_imm,shift,shift_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+7);
  } break;
  case SLV6_USAT16_ID: {
    Function *fct = module->getFunction("slv6_X_USAT16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g57.d);
    Value *m = ConstantInt::get(i8,instr.args.g57.m);
    Value *sat_imm = ConstantInt::get(i8,instr.args.g57.sat_imm);
    Value *cond = ConstantInt::get(i32,instr.args.g57.cond);
    Value *args[5] = {proc,d,m,sat_imm,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_USUB16_ID: {
    Function *fct = module->getFunction("slv6_X_USUB16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_USUB8_ID: {
    Function *fct = module->getFunction("slv6_X_USUB8"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_USUBADDX_ID: {
    Function *fct = module->getFunction("slv6_X_USUBADDX"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    Value *cond = ConstantInt::get(i32,instr.args.g5.cond);
    Value *args[5] = {proc,d,m,n,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UXTAB_ID: {
    Function *fct = module->getFunction("slv6_X_UXTAB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g59.d);
    Value *m = ConstantInt::get(i8,instr.args.g59.m);
    Value *n = ConstantInt::get(i8,instr.args.g59.n);
    Value *rotate = ConstantInt::get(i8,instr.args.g59.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g59.cond);
    Value *args[6] = {proc,d,m,n,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_UXTAB16_ID: {
    Function *fct = module->getFunction("slv6_X_UXTAB16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g59.d);
    Value *m = ConstantInt::get(i8,instr.args.g59.m);
    Value *n = ConstantInt::get(i8,instr.args.g59.n);
    Value *rotate = ConstantInt::get(i8,instr.args.g59.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g59.cond);
    Value *args[6] = {proc,d,m,n,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_UXTAH_ID: {
    Function *fct = module->getFunction("slv6_X_UXTAH"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g59.d);
    Value *m = ConstantInt::get(i8,instr.args.g59.m);
    Value *n = ConstantInt::get(i8,instr.args.g59.n);
    Value *rotate = ConstantInt::get(i8,instr.args.g59.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g59.cond);
    Value *args[6] = {proc,d,m,n,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_UXTB_ID: {
    Function *fct = module->getFunction("slv6_X_UXTB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g60.d);
    Value *m = ConstantInt::get(i8,instr.args.g60.m);
    Value *rotate = ConstantInt::get(i8,instr.args.g60.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g60.cond);
    Value *args[5] = {proc,d,m,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UXTB16_ID: {
    Function *fct = module->getFunction("slv6_X_UXTB16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g60.d);
    Value *m = ConstantInt::get(i8,instr.args.g60.m);
    Value *rotate = ConstantInt::get(i8,instr.args.g60.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g60.cond);
    Value *args[5] = {proc,d,m,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_UXTH_ID: {
    Function *fct = module->getFunction("slv6_X_UXTH"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g60.d);
    Value *m = ConstantInt::get(i8,instr.args.g60.m);
    Value *rotate = ConstantInt::get(i8,instr.args.g60.rotate);
    Value *cond = ConstantInt::get(i32,instr.args.g60.cond);
    Value *args[5] = {proc,d,m,rotate,cond};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_Tb_LDR1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDR1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g62.d);
    Value *n = ConstantInt::get(i8,instr.args.g62.n);
    Value *immed_5 = ConstantInt::get(i32,instr.args.g62.immed_5);
    IRB.CreateCall4(fct,proc,d,n,immed_5);
  } break;
  case SLV6_Tb_CPY_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_CPY"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_STR1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_STR1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g62.d);
    Value *n = ConstantInt::get(i8,instr.args.g62.n);
    Value *immed_5 = ConstantInt::get(i32,instr.args.g62.immed_5);
    IRB.CreateCall4(fct,proc,d,n,immed_5);
  } break;
  case SLV6_Tb_B1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_B1"); assert(fct);
    Value *cond = ConstantInt::get(i32,instr.args.g64.cond);
    Value *simmed_8_ext = ConstantInt::get(i32,instr.args.g64.simmed_8_ext);
    IRB.CreateCall3(fct,proc,cond,simmed_8_ext);
  } break;
  case SLV6_Tb_LSL1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LSL1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g65.d);
    Value *m = ConstantInt::get(i8,instr.args.g65.m);
    Value *immed_5 = ConstantInt::get(i32,instr.args.g65.immed_5);
    IRB.CreateCall4(fct,proc,d,m,immed_5);
  } break;
  case SLV6_Tb_ADD3_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ADD3"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g66.d);
    Value *m = ConstantInt::get(i8,instr.args.g66.m);
    Value *n = ConstantInt::get(i8,instr.args.g66.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_Tb_MOV1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_MOV1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g67.d);
    Value *immed_8 = ConstantInt::get(i8,instr.args.g67.immed_8);
    IRB.CreateCall3(fct,proc,d,immed_8);
  } break;
  case SLV6_Tb_CMP2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_CMP2"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g68.m);
    Value *n = ConstantInt::get(i8,instr.args.g68.n);
    IRB.CreateCall3(fct,proc,m,n);
  } break;
  case SLV6_Tb_LDR3_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDR3"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g67.d);
    Value *immed_8 = ConstantInt::get(i8,instr.args.g67.immed_8);
    IRB.CreateCall3(fct,proc,d,immed_8);
  } break;
  case SLV6_Tb_EOR_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_EOR"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_SUB2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_SUB2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g67.d);
    Value *immed_8 = ConstantInt::get(i8,instr.args.g67.immed_8);
    IRB.CreateCall3(fct,proc,d,immed_8);
  } break;
  case SLV6_Tb_MOV2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_MOV2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g69.d);
    Value *n = ConstantInt::get(i8,instr.args.g69.n);
    IRB.CreateCall3(fct,proc,d,n);
  } break;
  case SLV6_Tb_ADD2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ADD2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g67.d);
    Value *immed_8 = ConstantInt::get(i8,instr.args.g67.immed_8);
    IRB.CreateCall3(fct,proc,d,immed_8);
  } break;
  case SLV6_Tb_LDR4_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDR4"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g67.d);
    Value *immed_8 = ConstantInt::get(i8,instr.args.g67.immed_8);
    IRB.CreateCall3(fct,proc,d,immed_8);
  } break;
  case SLV6_Tb_AND_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_AND"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_LSR1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LSR1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g65.d);
    Value *m = ConstantInt::get(i8,instr.args.g65.m);
    Value *immed_5 = ConstantInt::get(i32,instr.args.g65.immed_5);
    IRB.CreateCall4(fct,proc,d,m,immed_5);
  } break;
  case SLV6_Tb_LDR2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDR2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g66.d);
    Value *m = ConstantInt::get(i8,instr.args.g66.m);
    Value *n = ConstantInt::get(i8,instr.args.g66.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_Tb_ADD4_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ADD4"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_CMP1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_CMP1"); assert(fct);
    Value *immed_8 = ConstantInt::get(i8,instr.args.g70.immed_8);
    Value *n = ConstantInt::get(i8,instr.args.g70.n);
    IRB.CreateCall3(fct,proc,immed_8,n);
  } break;
  case SLV6_Tb_ORR_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ORR"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_STR3_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_STR3"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g67.d);
    Value *immed_8 = ConstantInt::get(i8,instr.args.g67.immed_8);
    IRB.CreateCall3(fct,proc,d,immed_8);
  } break;
  case SLV6_Tb_ROR_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ROR"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g71.d);
    Value *s = ConstantInt::get(i8,instr.args.g71.s);
    IRB.CreateCall3(fct,proc,d,s);
  } break;
  case SLV6_Tb_BL_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_BL"); assert(fct);
    Value *H = ConstantInt::get(i32,instr.args.g72.H);
    Value *offset_11 = ConstantInt::get(i32,instr.args.g72.offset_11);
    IRB.CreateCall3(fct,proc,H,offset_11);
  } break;
  case SLV6_Tb_B2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_B2"); assert(fct);
    Value *simmed_11_ext = ConstantInt::get(i32,instr.args.g73.simmed_11_ext);
    IRB.CreateCall2(fct,proc,simmed_11_ext);
  } break;
  case SLV6_Tb_NEG_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_NEG"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_LDRB1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDRB1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g62.d);
    Value *n = ConstantInt::get(i8,instr.args.g62.n);
    Value *immed_5 = ConstantInt::get(i32,instr.args.g62.immed_5);
    IRB.CreateCall4(fct,proc,d,n,immed_5);
  } break;
  case SLV6_Tb_PUSH_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_PUSH"); assert(fct);
    Value *R = ConstantInt::get(i8,instr.args.g74.R);
    Value *register_list = ConstantInt::get(i32,instr.args.g74.register_list);
    IRB.CreateCall3(fct,proc,R,register_list);
  } break;
  case SLV6_Tb_POP_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_POP"); assert(fct);
    Value *R = ConstantInt::get(i8,instr.args.g74.R);
    Value *register_list = ConstantInt::get(i32,instr.args.g74.register_list);
    IRB.CreateCall3(fct,proc,R,register_list);
  } break;
  case SLV6_Tb_CMP3_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_CMP3"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g68.m);
    Value *n = ConstantInt::get(i8,instr.args.g68.n);
    IRB.CreateCall3(fct,proc,m,n);
  } break;
  case SLV6_Tb_SUB4_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_SUB4"); assert(fct);
    Value *immed_7 = ConstantInt::get(i32,instr.args.g75.immed_7);
    IRB.CreateCall2(fct,proc,immed_7);
  } break;
  case SLV6_Tb_ADD7_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ADD7"); assert(fct);
    Value *immed_7 = ConstantInt::get(i32,instr.args.g75.immed_7);
    IRB.CreateCall2(fct,proc,immed_7);
  } break;
  case SLV6_Tb_ADD6_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ADD6"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g67.d);
    Value *immed_8 = ConstantInt::get(i8,instr.args.g67.immed_8);
    IRB.CreateCall3(fct,proc,d,immed_8);
  } break;
  case SLV6_Tb_BX_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_BX"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g76.m);
    IRB.CreateCall2(fct,proc,m);
  } break;
  case SLV6_Tb_STRB1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_STRB1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g62.d);
    Value *n = ConstantInt::get(i8,instr.args.g62.n);
    Value *immed_5 = ConstantInt::get(i32,instr.args.g62.immed_5);
    IRB.CreateCall4(fct,proc,d,n,immed_5);
  } break;
  case SLV6_Tb_LDRB2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDRB2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g66.d);
    Value *m = ConstantInt::get(i8,instr.args.g66.m);
    Value *n = ConstantInt::get(i8,instr.args.g66.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_Tb_ADC_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ADC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_SUB3_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_SUB3"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g66.d);
    Value *m = ConstantInt::get(i8,instr.args.g66.m);
    Value *n = ConstantInt::get(i8,instr.args.g66.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_Tb_SUB1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_SUB1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g77.d);
    Value *n = ConstantInt::get(i8,instr.args.g77.n);
    Value *immed_3 = ConstantInt::get(i32,instr.args.g77.immed_3);
    IRB.CreateCall4(fct,proc,d,n,immed_3);
  } break;
  case SLV6_Tb_LSR2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LSR2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g71.d);
    Value *s = ConstantInt::get(i8,instr.args.g71.s);
    IRB.CreateCall3(fct,proc,d,s);
  } break;
  case SLV6_Tb_STR2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_STR2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g66.d);
    Value *m = ConstantInt::get(i8,instr.args.g66.m);
    Value *n = ConstantInt::get(i8,instr.args.g66.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_Tb_STRB2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_STRB2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g66.d);
    Value *m = ConstantInt::get(i8,instr.args.g66.m);
    Value *n = ConstantInt::get(i8,instr.args.g66.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_Tb_LDMIA_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDMIA"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g78.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g78.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g78.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_Tb_STMIA_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_STMIA"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g78.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g78.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g78.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_Tb_ADD1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ADD1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g77.d);
    Value *n = ConstantInt::get(i8,instr.args.g77.n);
    Value *immed_3 = ConstantInt::get(i32,instr.args.g77.immed_3);
    IRB.CreateCall4(fct,proc,d,n,immed_3);
  } break;
  case SLV6_Tb_MUL_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_MUL"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_ASR1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ASR1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g65.d);
    Value *m = ConstantInt::get(i8,instr.args.g65.m);
    Value *immed_5 = ConstantInt::get(i32,instr.args.g65.immed_5);
    IRB.CreateCall4(fct,proc,d,m,immed_5);
  } break;
  case SLV6_Tb_MVN_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_MVN"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_LDRH1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDRH1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g62.d);
    Value *n = ConstantInt::get(i8,instr.args.g62.n);
    Value *immed_5 = ConstantInt::get(i32,instr.args.g62.immed_5);
    IRB.CreateCall4(fct,proc,d,n,immed_5);
  } break;
  case SLV6_Tb_TST_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_TST"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g68.m);
    Value *n = ConstantInt::get(i8,instr.args.g68.n);
    IRB.CreateCall3(fct,proc,m,n);
  } break;
  case SLV6_Tb_BIC_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_BIC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_LSL2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LSL2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g71.d);
    Value *s = ConstantInt::get(i8,instr.args.g71.s);
    IRB.CreateCall3(fct,proc,d,s);
  } break;
  case SLV6_Tb_ADD5_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ADD5"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g67.d);
    Value *immed_8 = ConstantInt::get(i8,instr.args.g67.immed_8);
    IRB.CreateCall3(fct,proc,d,immed_8);
  } break;
  case SLV6_Tb_ASR2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_ASR2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g71.d);
    Value *s = ConstantInt::get(i8,instr.args.g71.s);
    IRB.CreateCall3(fct,proc,d,s);
  } break;
  case SLV6_Tb_BKPT_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_BKPT"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_Tb_BLX2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_BLX2"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g76.m);
    IRB.CreateCall2(fct,proc,m);
  } break;
  case SLV6_Tb_CMN_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_CMN"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g68.m);
    Value *n = ConstantInt::get(i8,instr.args.g68.n);
    IRB.CreateCall3(fct,proc,m,n);
  } break;
  case SLV6_Tb_CPS_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_CPS"); assert(fct);
    Value *A = ConstantInt::get(i8,instr.args.g79.A);
    Value *F = ConstantInt::get(i8,instr.args.g79.F);
    Value *I = ConstantInt::get(i8,instr.args.g79.I);
    Value *imod = ConstantInt::get(i8,instr.args.g79.imod);
    Value *args[5] = {proc,A,F,I,imod};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_Tb_LDRH2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDRH2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g66.d);
    Value *m = ConstantInt::get(i8,instr.args.g66.m);
    Value *n = ConstantInt::get(i8,instr.args.g66.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_Tb_LDRSB_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDRSB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g66.d);
    Value *m = ConstantInt::get(i8,instr.args.g66.m);
    Value *n = ConstantInt::get(i8,instr.args.g66.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_Tb_LDRSH_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDRSH"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g66.d);
    Value *m = ConstantInt::get(i8,instr.args.g66.m);
    Value *n = ConstantInt::get(i8,instr.args.g66.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_Tb_REV_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_REV"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g69.d);
    Value *n = ConstantInt::get(i8,instr.args.g69.n);
    IRB.CreateCall3(fct,proc,d,n);
  } break;
  case SLV6_Tb_REV16_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_REV16"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g69.d);
    Value *n = ConstantInt::get(i8,instr.args.g69.n);
    IRB.CreateCall3(fct,proc,d,n);
  } break;
  case SLV6_Tb_REVSH_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_REVSH"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g69.d);
    Value *n = ConstantInt::get(i8,instr.args.g69.n);
    IRB.CreateCall3(fct,proc,d,n);
  } break;
  case SLV6_Tb_SBC_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_SBC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_SETEND_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_SETEND"); assert(fct);
    Value *E = ConstantInt::get(i8,instr.args.g43.E);
    IRB.CreateCall2(fct,proc,E);
  } break;
  case SLV6_Tb_STRH1_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_STRH1"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g62.d);
    Value *n = ConstantInt::get(i8,instr.args.g62.n);
    Value *immed_5 = ConstantInt::get(i32,instr.args.g62.immed_5);
    IRB.CreateCall4(fct,proc,d,n,immed_5);
  } break;
  case SLV6_Tb_STRH2_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_STRH2"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g66.d);
    Value *m = ConstantInt::get(i8,instr.args.g66.m);
    Value *n = ConstantInt::get(i8,instr.args.g66.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_Tb_SWI_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_SWI"); assert(fct);
    IRB.CreateCall(fct,proc);
  } break;
  case SLV6_Tb_SXTB_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_SXTB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_SXTH_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_SXTH"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_UXTB_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_UXTB"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_Tb_UXTH_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_UXTH"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g63.d);
    Value *m = ConstantInt::get(i8,instr.args.g63.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_LDR_M2_ImmOff_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_ImmOff_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    IRB.CreateCall4(fct,proc,d,n,signed_offset_12);
  } break;
  case SLV6_STR_M2_ImmOff_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_ImmOff_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    IRB.CreateCall4(fct,proc,d,n,signed_offset_12);
  } break;
  case SLV6_B_L1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_B_L1_NC"); assert(fct);
    Value *pc_offset = ConstantInt::get(i32,instr.args.g2.pc_offset);
    IRB.CreateCall2(fct,proc,pc_offset);
  } break;
  case SLV6_B_L0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_B_L0_NC"); assert(fct);
    Value *pc_offset = ConstantInt::get(i32,instr.args.g2.pc_offset);
    IRB.CreateCall2(fct,proc,pc_offset);
  } break;
  case SLV6_SUB_M1_Imm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_Imm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SUB_M1_Imm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_Imm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_CMP_M1_Reg_NC_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_Reg_NC"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    IRB.CreateCall3(fct,proc,m,n);
  } break;
  case SLV6_ADD_M1_Imm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_Imm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADD_M1_Imm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_Imm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADD_M1_Reg_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_Reg_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_ADD_M1_Reg_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_Reg_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_EOR_M1_Reg_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_Reg_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_EOR_M1_Reg_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_Reg_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_AND_M1_Imm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_Imm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_AND_M1_Imm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_Imm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_LSRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    IRB.CreateCall4(fct,proc,d,m,shift_imm);
  } break;
  case SLV6_MOV_M1_LSRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    IRB.CreateCall4(fct,proc,d,m,shift_imm);
  } break;
  case SLV6_CPY_NC_ID: {
    Function *fct = module->getFunction("slv6_X_CPY_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g7.d);
    Value *m = ConstantInt::get(i8,instr.args.g7.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_MOV_M1_LSLImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSLImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    IRB.CreateCall4(fct,proc,d,m,shift_imm);
  } break;
  case SLV6_MOV_M1_LSLImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSLImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    IRB.CreateCall4(fct,proc,d,m,shift_imm);
  } break;
  case SLV6_MOV_M1_Imm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_Imm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g8.d);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g8.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g8.immed_rotated);
    IRB.CreateCall4(fct,proc,d,rotate_imm,immed_rotated);
  } break;
  case SLV6_MOV_M1_Imm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_Imm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g8.d);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g8.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g8.immed_rotated);
    IRB.CreateCall4(fct,proc,d,rotate_imm,immed_rotated);
  } break;
  case SLV6_LDM1_M4_IA_W1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDM1_M4_IA_W1_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_LDM1_M4_IA_W0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDM1_M4_IA_W0_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_CMP_M1_Imm_NC_ID: {
    Function *fct = module->getFunction("slv6_X_CMP_M1_Imm_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g10.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g10.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g10.immed_rotated);
    IRB.CreateCall4(fct,proc,n,rotate_imm,immed_rotated);
  } break;
  case SLV6_LDR_M2_ScRegOff_U1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_ScRegOff_U1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *args[6] = {proc,d,m,n,shift,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDR_M2_ScRegOff_U0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_ScRegOff_U0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *args[6] = {proc,d,m,n,shift,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_BX_NC_ID: {
    Function *fct = module->getFunction("slv6_X_BX_NC"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g12.m);
    IRB.CreateCall2(fct,proc,m);
  } break;
  case SLV6_ADD_M1_LSLImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_LSLImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADD_M1_LSLImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_LSLImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDRB_M2_ImmOff_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_ImmOff_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    IRB.CreateCall4(fct,proc,d,n,signed_offset_12);
  } break;
  case SLV6_ORR_M1_Reg_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_Reg_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_ORR_M1_Reg_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_Reg_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_MOV_M1_RRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_RRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    IRB.CreateCall4(fct,proc,d,m,shift_imm);
  } break;
  case SLV6_MOV_M1_RRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_RRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    IRB.CreateCall4(fct,proc,d,m,shift_imm);
  } break;
  case SLV6_LDR_M2_Imm_postInd_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_Imm_postInd_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    IRB.CreateCall4(fct,proc,d,n,signed_offset_12);
  } break;
  case SLV6_EOR_M1_RRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_RRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_EOR_M1_RRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_RRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_AND_M1_Reg_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_Reg_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_AND_M1_Reg_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_AND_M1_Reg_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_STR_M2_Imm_preInd_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_Imm_preInd_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    IRB.CreateCall4(fct,proc,d,n,signed_offset_12);
  } break;
  case SLV6_STRB_M2_ImmOff_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_ImmOff_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    IRB.CreateCall4(fct,proc,d,n,signed_offset_12);
  } break;
  case SLV6_ORR_M1_LSLImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_LSLImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_LSLImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_LSLImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADC_M1_Reg_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_Reg_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_ADC_M1_Reg_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADC_M1_Reg_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_LDRB_M2_RegOff_U1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_RegOff_U1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_LDRB_M2_RegOff_U0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_RegOff_U0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_RSB_M1_Reg_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_Reg_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_RSB_M1_Reg_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_Reg_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_BIC_M1_Imm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_Imm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_BIC_M1_Imm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_BIC_M1_Imm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MVN_M1_Imm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_Imm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g8.d);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g8.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g8.immed_rotated);
    IRB.CreateCall4(fct,proc,d,rotate_imm,immed_rotated);
  } break;
  case SLV6_MVN_M1_Imm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_Imm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g8.d);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g8.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g8.immed_rotated);
    IRB.CreateCall4(fct,proc,d,rotate_imm,immed_rotated);
  } break;
  case SLV6_ORR_M1_LSRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_LSRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_LSRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_LSRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_EOR_M1_LSRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_LSRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_EOR_M1_LSRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_LSRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDR_M2_RegOff_U1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_RegOff_U1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_LDR_M2_RegOff_U0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_RegOff_U0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_MOV_M1_LSRReg_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSRReg_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    IRB.CreateCall4(fct,proc,d,m,s);
  } break;
  case SLV6_MOV_M1_LSRReg_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSRReg_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    IRB.CreateCall4(fct,proc,d,m,s);
  } break;
  case SLV6_STRB_M2_RegOff_U1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_RegOff_U1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_STRB_M2_RegOff_U0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_RegOff_U0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_STR_M2_ScRegOff_U1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_ScRegOff_U1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *args[6] = {proc,d,m,n,shift,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_STR_M2_ScRegOff_U0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_ScRegOff_U0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *args[6] = {proc,d,m,n,shift,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_CMN_M1_Reg_NC_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_Reg_NC"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    IRB.CreateCall3(fct,proc,m,n);
  } break;
  case SLV6_STR_M2_Reg_postInd_U1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_Reg_postInd_U1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_STR_M2_Reg_postInd_U0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_Reg_postInd_U0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_STR_M2_RegOff_U1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_RegOff_U1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_STR_M2_RegOff_U0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_RegOff_U0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g5.d);
    Value *m = ConstantInt::get(i8,instr.args.g5.m);
    Value *n = ConstantInt::get(i8,instr.args.g5.n);
    IRB.CreateCall4(fct,proc,d,m,n);
  } break;
  case SLV6_EOR_M1_LSLImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_LSLImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_EOR_M1_LSLImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_LSLImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_RSB_M1_Imm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_Imm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_RSB_M1_Imm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_Imm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_ASRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_ASRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    IRB.CreateCall4(fct,proc,d,m,shift_imm);
  } break;
  case SLV6_MOV_M1_ASRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_ASRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g6.d);
    Value *m = ConstantInt::get(i8,instr.args.g6.m);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g6.shift_imm);
    IRB.CreateCall4(fct,proc,d,m,shift_imm);
  } break;
  case SLV6_ADD_M1_RRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_RRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADD_M1_RRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_RRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_RSB_M1_LSLImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_LSLImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_RSB_M1_LSLImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_LSLImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STRB_M2_Imm_postInd_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STRB_M2_Imm_postInd_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    IRB.CreateCall4(fct,proc,d,n,signed_offset_12);
  } break;
  case SLV6_STM1_M4_IA_W1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_IA_W1_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_STM1_M4_IA_W0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_IA_W0_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_TST_M1_Imm_NC_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_Imm_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g10.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g10.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g10.immed_rotated);
    IRB.CreateCall4(fct,proc,n,rotate_imm,immed_rotated);
  } break;
  case SLV6_STM1_M4_DB_W1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_DB_W1_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_STM1_M4_DB_W0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_DB_W0_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_MVN_M1_Reg_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_Reg_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g7.d);
    Value *m = ConstantInt::get(i8,instr.args.g7.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_MVN_M1_Reg_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MVN_M1_Reg_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g7.d);
    Value *m = ConstantInt::get(i8,instr.args.g7.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  case SLV6_STM1_M4_IB_W1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_IB_W1_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_STM1_M4_IB_W0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STM1_M4_IB_W0_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_ADD_M1_LSRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_LSRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ADD_M1_LSRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ADD_M1_LSRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_STR_M2_Imm_postInd_NC_ID: {
    Function *fct = module->getFunction("slv6_X_STR_M2_Imm_postInd_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    IRB.CreateCall4(fct,proc,d,n,signed_offset_12);
  } break;
  case SLV6_LDRB_M2_ScRegOff_U1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_ScRegOff_U1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *args[6] = {proc,d,m,n,shift,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_LDRB_M2_ScRegOff_U0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDRB_M2_ScRegOff_U0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g11.d);
    Value *m = ConstantInt::get(i8,instr.args.g11.m);
    Value *n = ConstantInt::get(i8,instr.args.g11.n);
    Value *shift = ConstantInt::get(i8,instr.args.g11.shift);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g11.shift_imm);
    Value *args[6] = {proc,d,m,n,shift,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+6);
  } break;
  case SLV6_SUB_M1_LSLImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_LSLImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SUB_M1_LSLImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_LSLImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_LDM1_M4_IB_W1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDM1_M4_IB_W1_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_LDM1_M4_IB_W0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDM1_M4_IB_W0_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g9.n);
    Value *nb_reg_x4 = ConstantInt::get(i8,instr.args.g9.nb_reg_x4);
    Value *register_list = ConstantInt::get(i32,instr.args.g9.register_list);
    IRB.CreateCall4(fct,proc,n,nb_reg_x4,register_list);
  } break;
  case SLV6_LDRH_M3_ImmOff_U1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDRH_M3_ImmOff_U1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g15.d);
    Value *n = ConstantInt::get(i8,instr.args.g15.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g15.immedHL);
    IRB.CreateCall4(fct,proc,d,n,immedHL);
  } break;
  case SLV6_LDRH_M3_ImmOff_U0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDRH_M3_ImmOff_U0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g15.d);
    Value *n = ConstantInt::get(i8,instr.args.g15.n);
    Value *immedHL = ConstantInt::get(i8,instr.args.g15.immedHL);
    IRB.CreateCall4(fct,proc,d,n,immedHL);
  } break;
  case SLV6_LDR_M2_Imm_preInd_NC_ID: {
    Function *fct = module->getFunction("slv6_X_LDR_M2_Imm_preInd_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g1.d);
    Value *n = ConstantInt::get(i8,instr.args.g1.n);
    Value *signed_offset_12 = ConstantInt::get(i32,instr.args.g1.signed_offset_12);
    IRB.CreateCall4(fct,proc,d,n,signed_offset_12);
  } break;
  case SLV6_SMULL_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_SMULL_S1_NC"); assert(fct);
    Value *dHi = ConstantInt::get(i8,instr.args.g16.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g16.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g16.m);
    Value *s = ConstantInt::get(i8,instr.args.g16.s);
    Value *args[5] = {proc,dHi,dLo,m,s};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SMULL_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_SMULL_S0_NC"); assert(fct);
    Value *dHi = ConstantInt::get(i8,instr.args.g16.dHi);
    Value *dLo = ConstantInt::get(i8,instr.args.g16.dLo);
    Value *m = ConstantInt::get(i8,instr.args.g16.m);
    Value *s = ConstantInt::get(i8,instr.args.g16.s);
    Value *args[5] = {proc,dHi,dLo,m,s};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_RSB_M1_ASRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_ASRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_RSB_M1_ASRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_RSB_M1_ASRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_TST_M1_Reg_NC_ID: {
    Function *fct = module->getFunction("slv6_X_TST_M1_Reg_NC"); assert(fct);
    Value *m = ConstantInt::get(i8,instr.args.g4.m);
    Value *n = ConstantInt::get(i8,instr.args.g4.n);
    IRB.CreateCall3(fct,proc,m,n);
  } break;
  case SLV6_EOR_M1_Imm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_Imm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_EOR_M1_Imm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_EOR_M1_Imm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_ASRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_ASRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_ASRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_ASRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_Imm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_Imm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_ORR_M1_Imm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_ORR_M1_Imm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g3.d);
    Value *n = ConstantInt::get(i8,instr.args.g3.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g3.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g3.immed_rotated);
    Value *args[5] = {proc,d,n,rotate_imm,immed_rotated};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SUB_M1_ASRImm_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_ASRImm_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_SUB_M1_ASRImm_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_SUB_M1_ASRImm_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g13.d);
    Value *m = ConstantInt::get(i8,instr.args.g13.m);
    Value *n = ConstantInt::get(i8,instr.args.g13.n);
    Value *shift_imm = ConstantInt::get(i8,instr.args.g13.shift_imm);
    Value *args[5] = {proc,d,m,n,shift_imm};
    IRB.CreateCall<Value**>(fct,args,args+5);
  } break;
  case SLV6_MOV_M1_LSLReg_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSLReg_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    IRB.CreateCall4(fct,proc,d,m,s);
  } break;
  case SLV6_MOV_M1_LSLReg_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MOV_M1_LSLReg_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    IRB.CreateCall4(fct,proc,d,m,s);
  } break;
  case SLV6_MUL_S1_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MUL_S1_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    IRB.CreateCall4(fct,proc,d,m,s);
  } break;
  case SLV6_MUL_S0_NC_ID: {
    Function *fct = module->getFunction("slv6_X_MUL_S0_NC"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g14.d);
    Value *m = ConstantInt::get(i8,instr.args.g14.m);
    Value *s = ConstantInt::get(i8,instr.args.g14.s);
    IRB.CreateCall4(fct,proc,d,m,s);
  } break;
  case SLV6_CMN_M1_Imm_NC_ID: {
    Function *fct = module->getFunction("slv6_X_CMN_M1_Imm_NC"); assert(fct);
    Value *n = ConstantInt::get(i8,instr.args.g10.n);
    Value *rotate_imm = ConstantInt::get(i8,instr.args.g10.rotate_imm);
    Value *immed_rotated = ConstantInt::get(i32,instr.args.g10.immed_rotated);
    IRB.CreateCall4(fct,proc,n,rotate_imm,immed_rotated);
  } break;
  case SLV6_Tb_LDR1_NI_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LDR1_NI"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g62.d);
    Value *n = ConstantInt::get(i8,instr.args.g62.n);
    IRB.CreateCall3(fct,proc,d,n);
  } break;
  case SLV6_Tb_LSL1_NI_ID: {
    Function *fct = module->getFunction("slv6_X_Tb_LSL1_NI"); assert(fct);
    Value *d = ConstantInt::get(i8,instr.args.g65.d);
    Value *m = ConstantInt::get(i8,instr.args.g65.m);
    IRB.CreateCall3(fct,proc,d,m);
  } break;
  default: abort();
  }
}
