init:
	cat init_database/init_script.sql | psql -h localhost -p5433  -U postgres -d postgres
delete:
	cat init_database/del_script.sql | psql -h localhost -p5433  -U postgres -d postgres