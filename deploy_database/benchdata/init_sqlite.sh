cat init_script_sqlite3.sql | sqlite3 bench.db
mv bench.db ../../server/cmake-build-debug/benchmark/bench.db
