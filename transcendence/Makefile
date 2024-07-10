DC := docker-compose -f docker-compose.yml

all:
	@mkdir -p /home/rturker/data/postgresql
	@mkdir -p /home/rturker/data/medias
	@mkdir -p /home/rturker/data/static
	@$(DC) up -d --build

down:
	@$(DC) down;

re: clean all

clean:
	@$(DC) down -v --remove-orphans
	@if [ "$$(docker images -q | wc -l)" -gt 0 ]; then docker rmi -f $$(docker images -q); fi

vol:
	@rm -rf /home/rturker/data/static
	@make down
	@docker volume rm $$(docker volume ls -q | grep dockerize_static)
	@make all


.PHONY: all down re clean vol