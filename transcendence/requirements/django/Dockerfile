FROM debian:latest

RUN mkdir -p /home/rturker/django
WORKDIR /home/rturker/django

RUN apt-get update && apt-get upgrade && apt-get install -y python3 python3-pip python3-venv redis-server

COPY ./req.txt /home/rturker/django
RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"
RUN pip3 install -r /home/rturker/django/req.txt

COPY ./ft_transcendence /home/rturker/django

COPY ./medias /vol/medias
COPY ./static /vol/static
COPY ./script.sh /home/rturker/django

EXPOSE 8000
EXPOSE 3000

CMD ["bash", "script.sh"]
