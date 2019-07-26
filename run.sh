IMAGE_NAME="zhanj7_v1.4:rapidnet"
COMMAND="/bin/bash"

MNT_FROM="/Users/milliondegree/Documents/rapidnet_v1.0/"
MNT_TO="/home/${USER}/rapidenet_v1.0/"

#-i interactive
#-t stdin/stdout
#-P port remapping
#-v <from>:<to> | volume mounting

# docker run -i -t -P -v ${MNT_FROM}:${MNT_TO} ${IMAGE_NAME} ${COMMAND}
docker run -i -t \
    --name milliondegree\
    -v ${MNT_FROM}:${MNT_TO} \
    ${IMAGE_NAME} \
    ${COMMAND}
