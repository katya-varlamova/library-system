init:
	cat database_prepare/init_script.sql | psql -h localhost -p5433  -U postgres -d postgres
delete:
	cat database_prepare/del_script.sql | psql -h localhost -p5433  -U postgres -d postgres


init_sqlite3: 
	cat database_prepare/init_script_sqlite3.sql | sqlite3 librarysystem.db
	mv librarysystem.db server/cmake-build-debug/librarysystem.db
delete_sqlite3:
	cat database_prepare/del_script_sqlite3.sql | sqlite3 server/cmake-build-debug/librarysystem.db