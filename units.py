import json
import requests

jstrs = [
         json.dumps({"author" : "gogol",
                   "name" : "vechera na hutore",
                   "library" :{"name" : "ln1",
                               "address" : "molodogvardeyskaya 5"}}),
         json.dumps({"author" : "gogol",
                   "name" : "mertvie dushi",
                   "library" :{"name" : "ln2",
                               "address" : "ivana franko"}}),
         json.dumps({"author" : "gogol",
                   "name" : "mertvie dushi",
                   "library" :{"name" : "ln1",
                               "address" : "molodogvardeyskaya 5"}}),
         json.dumps({"author" : "gogol",
                   "name" : "vechera na hutore",
                   "library" : {"name" : "ln2",
                                "address" : "ivana franko"}}),
         ]

reg = json.dumps({"account" : {"name" : "admin",
                               "login" : "admin",
                               "password": "admin",
                               "role" : "admin"}})
par = {"role" : "admin"}
headers = {'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.post("http://127.0.0.1:8000/api/v1/registration",
                 params=par,
                 headers=headers,
                 data = reg)
if r.status_code == 200:
    print("post admin account passed")
else:
    print("post admin account failed")
headers = {'login': 'admin', 'password': 'admin', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/login",
                 headers=headers)

if r.json() == {'account': {'id': 1, 'name': 'admin', 'login': 'admin', 'password': 'admin', 'role': 'admin'}}:
    print("get admin account passed")
else:
    print("get admin account failed")

reg = json.dumps({"account" : {"name" : "katya_varlamova",
                               "login" : "katya_varlamova",
                               "password": "12345",
                               "role" : "reader"},
                  "phone": "89961008307"})
par = {"role" : "reader"}
headers = {'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.post("http://127.0.0.1:8000/api/v1/registration",
                 params=par,
                 headers=headers,
                 data = reg)
if r.status_code == 200:
    print("post reader account passed")
else:
    print("post reader account failed")
headers = {'login': 'katya_varlamova', 'password': '12345', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/login",
                 headers=headers)

if r.json() == {'account': {'id': 2, 'name': 'katya_varlamova', 'login': 'katya_varlamova', 'password': '12345', 'role': 'reader'}, 'phone': '89961008307'}:
    print("get reader account passed")
else:
    print("get reader account failed")

for st in jstrs:
    headers = {"password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
    r = requests.post("http://127.0.0.1:8000/api/v1/book",
                     data=st,
                     params={"login" : "admin"},
                     headers=headers) 
par = {}
headers = {"login": "katya_varlamova", "password" : "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 params=par,
                 headers=headers)

if r.json() != {'books': [{'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}},
                          {'id': 1, 'name': 'vechera na hutore', 'author': 'gogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}},
                          {'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 2, 'name': 'ln2', 'address': 'ivana franko'}},
                          {'id': 4, 'name': 'vechera na hutore', 'author': 'gogol', 'library': {'id': 2, 'name': 'ln2', 'address': 'ivana franko'}}]}:
    print("error books post")
else:
    print("books post passed")

par = {"name" : "vechera na hutore", "lib_address" : "ivana franko"}
headers = {"login": "katya_varlamova", "password" : "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 params=par,
                 headers=headers)

if r.json() != {'books': [{'id': 4, 'name': 'vechera na hutore', 'author': 'gogol', 'library': {'id': 2, 'name': 'ln2', 'address': 'ivana franko'}}]}:
    print("error books get")
else:
    print("books get passed")

reg = json.dumps({"account" : {"name" : "librarian1",
                               "login" : "katya_librarian",
                               "password": "12345",
                               "role" : "librarian"},
                  "library" : {"name" : "ln2",
                               "address" : "ivana franko"}})
par = {"role" : "librarian"}
headers = {'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.post("http://127.0.0.1:8000/api/v1/registration",
                 params=par,
                 headers=headers,
                 data = reg)

if r.status_code == 200:
    print("post librarian account passed")
else:
    print("post librarian account failed")
headers = {'login': 'katya_librarian', 'password': '12345', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/login",
                 headers=headers)

if r.json() == {'account': {'id': 3, 'name': 'librarian1', 'login': 'katya_librarian', 'password': '12345', 'role': 'librarian'}, 'library': {'id': 2, 'name': 'ln2', 'address': 'ivana franko'}}:
    print("get librarian account passed")
else:
    print("get librarian account failed")

par = {"author" : "gogol", "name" : "mertvie dushi", "login_user" : "katya_varlamova"}
headers = {"login" : "katya_librarian", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/book/give",
                 params=par,
                 headers=headers)

par = {"login" : "katya_varlamova"}
headers = {"login": "katya_varlamova", "password" : "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 params=par,
                 headers=headers)

if r.json() != {'books': [{'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 2, 'name': 'ln2', 'address': 'ivana franko'}}]}:
    print("update1 books error")
else:
    print("update1 books passed")

    

par = {"author" : "gogol", "name" : "mertvie dushi", "login_user" : "katya_varlamova"}
headers = {"login" : "katya_librarian", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/book/return",
                 params=par,
                 headers=headers)

par = {"login" : "katya_varlamova"}
headers = {"login": "katya_varlamova", "password" : "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 params=par,
                 headers=headers)
if r.json() != {'books': []}:
    print("update2 books error")
else:
    print("update2 books passed")


headers = {'login': 'katya_varlamova', 'password': '12345', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers)

if r.json() == {'libraries': [{'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}, {'id': 2, 'name': 'ln2', 'address': 'ivana franko'}]}:
    print("get1 libraries passed")
else:
    print("get1 Libraries failed")

par = {"address" : "molodogvardeyskaya 5"}
headers = {'login': 'katya_varlamova', 'password': '12345', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers,
                 params = par)

if r.json() == {'libraries': [{'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}]}:
    print("get2 libraries passed")
else:
    print("get2 Libraries failed")


    
body = json.dumps({"account" : {"name" : "katya_varlamova_upd",
                               "login" : "katya_varlamova_upd",
                               "password": "123456",
                               "role" : "reader"},
                  "phone": "89961008308"})
headers = {"login" : "katya_varlamova", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/account",
                 params=par,
                 headers=headers,
                 data = body)
headers = {'login': 'katya_varlamova_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/login",
                 headers=headers)

if r.json() == {'account': {'id': 2, 'name': 'katya_varlamova_upd', 'login': 'katya_varlamova_upd', 'password': '123456', 'role': 'reader'}, 'phone': '89961008308'}:
    print("update reader account passed")
else:
    print("update reader account failed")



body = json.dumps({"account" : {"name" : "librarian1_upd",
                               "login" : "katya_librarian_upd",
                               "password": "123456",
                               "role" : "librarian"},
                  "library" : {"id": 1,
                               "name" : "ln2",
                               "address" : "ivana franko"}})
headers = {"login" : "katya_librarian", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/account",
                 params=par,
                 headers=headers,
                 data = body)
headers = {'login': 'katya_librarian_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/login",
                 headers=headers)
if r.json() == {'account': {'id': 3, 'name': 'librarian1_upd', 'login': 'katya_librarian_upd', 'password': '123456', 'role': 'librarian'},
               'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}}:
    print("update librarian account passed")
else:
    print("update librarian account failed")





body = json.dumps({"id": 2,
                   "name" : "lib_name2",
                   "address" : "ivana franko, 6"})
headers = {"login" : "katya_varlamova_upd", "password": "123456", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/library",
                 params=par,
                 headers=headers,
                 data = body)

headers = {'login': 'katya_varlamova_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers)
if r.json() == {'libraries': [{'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}, {'id': 2, 'name': 'ln2', 'address': 'ivana franko'}]}:
    print("wrong put libraries passed")
else:
    print("wtong put Libraries failed")

headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/library",
                 params=par,
                 headers=headers,
                 data = body)
headers = {'login': 'katya_varlamova_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers)

if r.json() == {'libraries': [{'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}, {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}]}:
    print("put libraries passed")
else:
    print("put Libraries failed")





body = json.dumps({"id": 5,
                   "name" : "lib_name3",
                   "address" : "yartsevskaya, 7"})
headers = {"login" : "katya_varlamova_upd", "password": "123456", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.post("http://127.0.0.1:8000/api/v1/library",
                 params=par,
                 headers=headers,
                 data = body)

headers = {'login': 'katya_varlamova_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers)
if r.json() == {'libraries': [{'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'},
                              {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}]}:
    print("wrong post libraries passed")
else:
    print("wtong post Libraries failed")

headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.post("http://127.0.0.1:8000/api/v1/library",
                 params=par,
                 headers=headers,
                 data = body)
headers = {'login': 'katya_varlamova_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers)
if r.json() == {'libraries': [{'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'},
                              {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'},
                              {"id": 3, "name" : "lib_name3", "address" : "yartsevskaya, 7"}]}:
    print("post libraries passed")
else:
    print("post Libraries failed")




body = json.dumps({"author" : "gogol-mogol",
                   "id" : 1, 
                   "name" : "vechera na hutore bliz dikanki",
                   "library" :{"id": 1,
                               "name" : "ln1",
                               "address" : "molodogvardeyskaya 5"}})
headers = {"login" : "katya_varlamova_upd", "password": "123456", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/book",
                 headers=headers,
                 data = body)
headers = {'login': 'katya_varlamova_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 headers=headers)

if r.json() == {'books': [{'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}}, {'id': 1, 'name': 'vechera na hutore', 'author': 'gogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}}, {'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}}, {'id': 4, 'name': 'vechera na hutore', 'author': 'gogol', 'library': {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}}]}:
    print("wrong put books passed")
else:
    print("wtong put books failed")




body = json.dumps({"author" : "gogol-mogol",
                   "id" : 1, 
                   "name" : "vechera na hutore bliz dikanki",
                   "library" :{"id": 1,
                               "name" : "ln1",
                               "address" : "molodogvardeyskaya 5"}})
headers = {"login" : "katya_varlamova_upd", "password": "123456", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/book",
                 headers=headers,
                 data = body)
headers = {'login': 'katya_varlamova_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 headers=headers)

if r.json() == {'books': [{'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}},
                          {'id': 1, 'name': 'vechera na hutore', 'author': 'gogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}},
                          {'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}},
                          {'id': 4, 'name': 'vechera na hutore', 'author': 'gogol', 'library': {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}}]}:
    print("wrong put books passed")
else:
    print("wtong put books failed")
headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/book",
                 headers=headers,
                 data = body)
headers = {'login': 'admin', 'password': 'admin', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 headers=headers)

if r.json() == {'books': [{'id': 1, 'name': 'vechera na hutore bliz dikanki', 'author': 'gogol-mogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}},
                          {'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}},
                          {'id': 4, 'name': 'vechera na hutore bliz dikanki', 'author': 'gogol-mogol', 'library': {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}},
                          {'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}}]}:
    print("put books passed")
else:
    print("put books failed")



par = {"id" : 1}
headers = {"login" : "katya_varlamova_upd", "password": "123456", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.delete("http://127.0.0.1:8000/api/v1/book",
                    headers=headers,
                    params = par)
headers = {'login': 'katya_varlamova_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 headers=headers)

if r.json() == {'books': [{'id': 1, 'name': 'vechera na hutore bliz dikanki', 'author': 'gogol-mogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}},
                          {'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}},
                          {'id': 4, 'name': 'vechera na hutore bliz dikanki', 'author': 'gogol-mogol', 'library': {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}},
                          {'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}}]}:
    print("wrong delete books passed")
else:
    print("wtong delete books failed")

headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.delete("http://127.0.0.1:8000/api/v1/book",
                    headers=headers,
                    params = par)
headers = {'login': 'admin', 'password': 'admin'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 headers=headers)

if r.json() == {'books': [{'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}},
                          {'id': 4, 'name': 'vechera na hutore bliz dikanki', 'author': 'gogol-mogol', 'library': {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}},
                          {'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'library': {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'}}]}:
    print("delete books passed")
else:
    print("delete books failed")


headers = {'login': 'katya_librarian_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.delete("http://127.0.0.1:8000/api/v1/account",
                    headers=headers)
if r.status_code != 200:
    print("delete librarian account failed")
    
headers = {'login': 'katya_librarian_upd', 'password': '123456'}
r = requests.get("http://127.0.0.1:8000/api/v1/login",
                 headers=headers)

if r.status_code == 500:
    print("delete librarian account passed")
else:
    print("delete librarian account failed")



par = {"id" : 1}
headers = {"login" : "katya_varlamova_upd", "password": "123456", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.delete("http://127.0.0.1:8000/api/v1/library",
                    headers=headers,
                    params = par)
headers = {'login': 'katya_varlamova_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers)

if r.json() == {'libraries': [{'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'},
                              {'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'},
                              {"id": 3, "name" : "lib_name3", "address" : "yartsevskaya, 7"}]}:
    print("wrong delete libraries passed")
else:
    print("wtong delete libraries failed")

headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.delete("http://127.0.0.1:8000/api/v1/library",
                    headers=headers,
                    params = par)
headers = {'login': 'admin', 'password': 'admin'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers)

if r.json() == {'libraries': [{'id': 2, 'name': 'lib_name2', 'address': 'ivana franko, 6'},
                              {"id": 3, "name" : "lib_name3", "address" : "yartsevskaya, 7"}]}:
    print("delete libraries passed")
else:
    print("delete libraries failed")



headers = {"login" : "katya_varlamova_upd", "password": "123456", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.delete("http://127.0.0.1:8000/api/v1/account",
                    headers=headers)
if r.status_code != 200:
    print("delete reader account failed")
    
headers = {"login" : "katya_varlamova_upd", "password": "123456"}
r = requests.get("http://127.0.0.1:8000/api/v1/login",
                 headers=headers)

if r.status_code == 500:
    print("delete reader account passed")
else:
    print("delete reader account failed")



headers = {'login': 'admin', 'password': 'admin', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.delete("http://127.0.0.1:8000/api/v1/account",
                    headers=headers)
if r.status_code != 200:
    print("delete admin account failed")
    
headers = {'login': 'admin', 'password': 'admin'}
r = requests.get("http://127.0.0.1:8000/api/v1/login",
                 headers=headers)

if r.status_code == 500:
    print("delete admin account passed")
else:
    print("delete admin account failed")
