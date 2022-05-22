init:
	cat database_prepare/init_script.sql | psql -h localhost -p5433  -U postgres -d postgres
delete:
	cat database_prepare/del_script.sql | psql -h localhost -p5433  -U postgres -d postgres