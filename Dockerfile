FROM debian
ADD docker/lib /usr/lib/x86_64-linux-gnu
ADD iptv_api /iptv_api
VOLUME ["/home/media"]
CMD /iptv_api
# docker run -it -v /home/media:/home/media --net=host iptv-api


