#! /bin/bash

SCRIPTPATH=$(cd $(dirname ${0}); pwd -P)

source ${SCRIPTPATH}/variant_configuration.bash

SWPATH=$(realpath ${SCRIPTPATH}/../../../../../../../../../..)
 
TMPPATH=$(mktemp -d --suffix=-libcudacxx__host_${hostarch}_${hostos}__target_${targetarch}_${targetos}__${compiler}) 
LIBCUDA=$(ldconfig -p | grep libcuda.so | tr ' ' '\n' | grep / | tr '\n' ' ' | sed 's/ *$//')
LIBNVIDIAFATBINARYLOADER=$(ldconfig -p | grep libnvidia-fatbinaryloader.so | tr ' ' '\n' | grep / | tr '\n' ' ' | sed 's/ *$//')
LIBNVIDIAPTXJITCOMPILER=$(ldconfig -p | grep libnvidia-ptxjitcompiler.so | tr ' ' '\n' | grep / | tr '\n' ' ' | sed 's/ *$//')

echo "CUDA driver libraries found:"

for library in ${LIBCUDA} ${LIBNVIDIAFATBINARYLOADER} ${LIBNVIDIAPTXJITCOMPILER}
do
  echo "  ${library}"
done

cp ${LIBCUDA} ${LIBNVIDIAFATBINARYLOADER} ${LIBNVIDIAPTXJITCOMPILER} ${TMPPATH}

if [ "$?" != "0" ]; then exit 1; fi

docker -D build \
  -t libcudacxx:host_${HOSTARCH}_${HOSTOS}__target_${TARGETARCH}_${TARGETOS}__${COMPILER} \
  -f ${SWPATH}/gpgpu/libcudacxx/docker/host/${HOSTARCH}/${HOSTOS}/target/${TARGETARCH}/${TARGETOS}/${COMPILER}/Dockerfile \
  ${TMPPATH}

if [ "$?" != "0" ]; then exit 1; fi

rm ${TMPPATH}/*
rmdir ${TMPPATH}

