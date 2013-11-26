function useensta ()
{
  source "/usr/ensta/etc/$1_env.sh"
}
useensta virtualsoc

export VSOC_APP_DIR=${PWD}
export VSOC_SRC_DIR=$PWD/../virtualsoc/include
export OWN_VIRTUALSOC_DIR="$PWD/../bin"
export VSOC_ROOT_DIR="$OWN_VIRTUALSOC_DIR"
export PATH=${OWN_VIRTUALSOC_DIR}:${PATH}

echo "Environment variables are set for apps!"
