host=$1
db=$2
cat database_prepare/del_script.sql | psql -h $host -p5433  -U postgres -d $db
