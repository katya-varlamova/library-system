import json
import requests

books = [
         json.dumps({"author" : "gogol",
                   "name" : "vechera na hutore",
                   "lib_id" : 2}),
         json.dumps({"author" : "gogol",
                   "name" : "mertvie dushi",
                   "lib_id" : 2}),
         json.dumps({"author" : "gogol",
                   "name" : "mertvie dushi",
                   "lib_id" : 2}),
         json.dumps({"author" : "gogol",
                   "name" : "vechera na hutore",
                   "lib_id" : 2}),
         ]

ebooks = [
         json.dumps({"author" : "gogol",
                   "name" : "vechera na hutore",
                   "link" : "https"}),
         json.dumps({"author" : "gogol",
                   "name" : "mertvie dushi",
                   "link" : "https"}),
         json.dumps({"author" : "gogol",
                   "name" : "mertvie dushi",
                   "link" : "https"}),
         json.dumps({"author" : "gogol",
                   "name" : "vechera na hutore",
                   "link" : "https"}),
         ]
libs = [
         json.dumps({"name" : "ln1",
                     "address" : "molodogvardeyskaya 5"}),
         json.dumps({"name" : "ln2",
                                "address" : "ivana franko"}),
        ]

headers = {'login': 'admin', 'password': 'admin', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/login",
                 headers=headers)

if r.json() == {'id': 1, 'name': 'admin', 'login': 'admin', 'password': 'admin',
                'role': 'admin', 'admin_acc': {}, 'librarian_acc': None, 'reader_acc': None}:
    print("get admin account passed")
else:
    print("get admin account failed")

reg = json.dumps({"name" : "katya_varlamova",
                  "login" : "katya_varlamova",
                  "password": "12345",
                  "role" : "reader", 'admin_acc': None, 'librarian_acc': None, 'reader_acc': {"phone": "89961008307"}})

headers = {'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.post("http://127.0.0.1:8000/api/v1/registration",
                 headers=headers,
                 data = reg)
if r.status_code == 200:
    print("post reader account passed")
else:
    print("post reader account failed")
headers = {'login': 'katya_varlamova', 'password': '12345', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/login",
                 headers=headers)

if r.json() == {'id': 2,
                'name': 'katya_varlamova', 'login': 'katya_varlamova',
                'password': '12345', 'role': 'reader', 'admin_acc': None, 'librarian_acc': None,
                'reader_acc': {'phone': '89961008307'}}:
    print("get reader account passed")
else:
    print("get reader account failed")

for st in libs:
    headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
    r = requests.post("http://127.0.0.1:8000/api/v1/library",
                      data=st,
                      headers=headers)
    if r.status_code == 200:
        print("post library passed")
    else:
        print("post library failed")
headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers = headers)
if r.json() == {'libraries': [{'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'},
                              {'id': 2, 'name': 'ln2', 'address': 'ivana franko'}]}:
    print("get libraries passed")
else:
    print("get libraries failed")

par = {"id" : 1}
headers = {"login" : "katya_varlamova", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.delete("http://127.0.0.1:8000/api/v1/library",
                    headers=headers,
                    params = par)
headers = {'login': 'katya_varlamova', 'password': '12345', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers)

if r.json() == {'libraries': [{'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'},
                              {'id': 2, 'name': 'ln2', 'address': 'ivana franko'}]}:
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

if r.json() == {'libraries': [{'id': 2, 'name': 'ln2', 'address': 'ivana franko'}]}:
    print("delete libraries passed")
else:
    print("delete libraries failed")


body = json.dumps({"id": 2,
                   "name" : "lib_name2",
                   "address" : "ivana franko, 6"})
headers = {"login" : "katya_varlamova", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/library",
                 params=par,
                 headers=headers,
                 data = body)

headers = {'login': 'katya_varlamova', 'password': '12345', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers)
if r.json() == {'libraries': [{'id': 2, 'name': 'ln2', 'address': 'ivana franko'}]}:
    print("wrong put libraries passed")
else:
    print("wtong put libraries failed")

headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/library",
                 params=par,
                 headers=headers,
                 data = body)
headers = {'login': 'katya_varlamova', 'password': '12345', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/library",
                 headers=headers)

if r.json() == {'libraries': [{"id": 2,
                               "name" : "lib_name2",
                               "address" : "ivana franko, 6"}]}:
    print("put libraries passed")
else:
    print("put Libraries failed")

reg = json.dumps({"name" : "librarian1",
                  "login" : "katya_librarian",
                  "password": "12345",
                  "role" : "librarian",
                  'admin_acc': None, 'librarian_acc': {'lib_id' : 2}, 'reader_acc': None})

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

if r.json() == {'id': 3, 'name': 'librarian1', 'login': 'katya_librarian', 'password': '12345', 'role': 'librarian',
                'admin_acc': None, 'librarian_acc': {'lib_id' : 2}, 'reader_acc': None}:
    print("get librarian account passed")
else:
    print("get librarian account failed")



for st in books:
    headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
    r = requests.post("http://127.0.0.1:8000/api/v1/book",
                      data=st,
                      headers=headers)
    if r.status_code == 200:
        print("post book passed")
    else:
        print("post book failed")
headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 headers = headers)
if r.json() =={'books': [{'id': 1, 'name': 'vechera na hutore', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 4, 'name': 'vechera na hutore', 'author': 'gogol', 'lib_id': 2, 'login': ''}]}:
    print("get books passed")
else:
    print("get books failed")
    


par = {"book_id" : 1, "login_user" : "katya_varlamova"}
headers = {"login" : "katya_librarian", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/book/give",
                 params=par,
                 headers=headers)

par = {"login_filter" : "katya_varlamova"}
headers = {"login": "katya_varlamova", "password" : "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 params=par,
                 headers=headers)


if r.json() != {'books': [{'id': 1, 'name': 'vechera na hutore', 'author': 'gogol',
                           'lib_id': 2, 'login': 'katya_varlamova'}
                         ]}:
    print("update1 books error")
else:
    print("update1 books passed")

par = {"book_id" : 1, "login_user" : "katya_varlamova"}
headers = {"login" : "katya_librarian", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/book/return",
                 params=par,
                 headers=headers)

par = {"login_filter" : "katya_varlamova"}
headers = {"login": "katya_varlamova", "password" : "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 params=par,
                 headers=headers)
if r.json() != {'books': []}:
    print("update2 books error")
else:
    print("update2 books passed")


body = json.dumps({"author" : "gogol-mogol",
                   "id" : 1, 
                   "name" : "vechera na hutore bliz dikanki",
                   "lib_id" : 2})
headers = {"login" : "katya_varlamova", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.put("http://127.0.0.1:8000/api/v1/book",
                 headers=headers,
                 data = body)
headers = {'login': 'katya_varlamova', 'password': '12345', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 headers=headers)

if r.json() =={'books': [{'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 4, 'name': 'vechera na hutore', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 1, 'name': 'vechera na hutore', 'author': 'gogol', 'lib_id': 2, 'login': ''}]}:
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

if r.json() =={'books': [{'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 4, 'name': 'vechera na hutore bliz dikanki', 'author': 'gogol-mogol', 'lib_id': 2, 'login': ''},
                         {'id': 1, 'name': 'vechera na hutore bliz dikanki', 'author': 'gogol-mogol', 'lib_id': 2, 'login': ''}]}:
    print("put books passed")
else:
    print("put books failed")

par = {"id" : 1}
headers = {"login" : "katya_varlamova", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.delete("http://127.0.0.1:8000/api/v1/book",
                    headers=headers,
                    params = par)
headers = {'login': 'katya_varlamova', 'password': '12345', 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/book",
                 headers=headers)

if r.json() =={'books': [{'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 4, 'name': 'vechera na hutore bliz dikanki', 'author': 'gogol-mogol', 'lib_id': 2, 'login': ''},
                         {'id': 1, 'name': 'vechera na hutore bliz dikanki', 'author': 'gogol-mogol', 'lib_id': 2, 'login': ''}]}:
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

if r.json() =={'books': [{'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'lib_id': 2, 'login': ''},
                         {'id': 4, 'name': 'vechera na hutore bliz dikanki', 'author': 'gogol-mogol', 'lib_id': 2, 'login': ''}]}:
    print("delete books passed")
else:
    print("delete books failed")




for st in ebooks:
    headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
    r = requests.post("http://127.0.0.1:8000/api/v1/ebook",
                      data=st,
                      headers=headers)
    if r.status_code == 200:
        print("post ebook passed")
    else:
        print("post ebook failed")
headers = {"login" : "admin", "password": "admin", 'Content-type': 'application/json', 'Accept': 'text/'}
r = requests.get("http://127.0.0.1:8000/api/v1/ebook",
                 headers = headers)
if r.json() =={'books': [{'id': 1, 'name': 'vechera na hutore', 'author': 'gogol', 'link': 'https'},
                         {'id': 2, 'name': 'mertvie dushi', 'author': 'gogol', 'link': 'https'},
                         {'id': 3, 'name': 'mertvie dushi', 'author': 'gogol', 'link': 'https'},
                         {'id': 4, 'name': 'vechera na hutore', 'author': 'gogol', 'link': 'https'}]}:
    print("get books passed")
else:
    print("get books failed")   
##body = json.dumps({"account" : {"name" : "katya_varlamova_upd",
##                               "login" : "katya_varlamova_upd",
##                               "password": "123456",
##                               "role" : "reader"},
##                  "phone": "89961008308"})
##headers = {"login" : "katya_varlamova", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
##r = requests.put("http://127.0.0.1:8000/api/v1/account",
##                 params=par,
##                 headers=headers,
##                 data = body)
##headers = {'login': 'katya_varlamova_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
##r = requests.get("http://127.0.0.1:8000/api/v1/login",
##                 headers=headers)
##
##if r.json() == {'account': {'id': 2, 'name': 'katya_varlamova_upd', 'login': 'katya_varlamova_upd', 'password': '123456', 'role': 'reader'}, 'phone': '89961008308'}:
##    print("update reader account passed")
##else:
##    print("update reader account failed")
##
##
##
##body = json.dumps({"account" : {"name" : "librarian1_upd",
##                               "login" : "katya_librarian_upd",
##                               "password": "123456",
##                               "role" : "librarian"},
##                  "library" : {"id": 1,
##                               "name" : "ln2",
##                               "address" : "ivana franko"}})
##headers = {"login" : "katya_librarian", "password": "12345", 'Content-type': 'application/json', 'Accept': 'text/'}
##r = requests.put("http://127.0.0.1:8000/api/v1/account",
##                 params=par,
##                 headers=headers,
##                 data = body)
##headers = {'login': 'katya_librarian_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
##r = requests.get("http://127.0.0.1:8000/api/v1/login",
##                 headers=headers)
##if r.json() == {'account': {'id': 3, 'name': 'librarian1_upd', 'login': 'katya_librarian_upd', 'password': '123456', 'role': 'librarian'},
##               'library': {'id': 1, 'name': 'ln1', 'address': 'molodogvardeyskaya 5'}}:
##    print("update librarian account passed")
##else:
##    print("update librarian account failed")
##
##

##
##
##
##
##headers = {'login': 'katya_librarian_upd', 'password': '123456', 'Content-type': 'application/json', 'Accept': 'text/'}
##r = requests.delete("http://127.0.0.1:8000/api/v1/account",
##                    headers=headers)
##if r.status_code != 200:
##    print("delete librarian account failed")
##    
##headers = {'login': 'katya_librarian_upd', 'password': '123456'}
##r = requests.get("http://127.0.0.1:8000/api/v1/login",
##                 headers=headers)
##
##if r.status_code == 500:
##    print("delete librarian account passed")
##else:
##    print("delete librarian account failed")
##
##
##

##
##
##
##headers = {"login" : "katya_varlamova_upd", "password": "123456", 'Content-type': 'application/json', 'Accept': 'text/'}
##r = requests.delete("http://127.0.0.1:8000/api/v1/account",
##                    headers=headers)
##if r.status_code != 200:
##    print("delete reader account failed")
##    
##headers = {"login" : "katya_varlamova_upd", "password": "123456"}
##r = requests.get("http://127.0.0.1:8000/api/v1/login",
##                 headers=headers)
##
##if r.status_code == 500:
##    print("delete reader account passed")
##else:
##    print("delete reader account failed")
##
##
##
##headers = {'login': 'admin', 'password': 'admin', 'Content-type': 'application/json', 'Accept': 'text/'}
##r = requests.delete("http://127.0.0.1:8000/api/v1/account",
##                    headers=headers)
##if r.status_code != 200:
##    print("delete admin account failed")
##    
##headers = {'login': 'admin', 'password': 'admin'}
##r = requests.get("http://127.0.0.1:8000/api/v1/login",
##                 headers=headers)
##
##if r.status_code == 500:
##    print("delete admin account passed")
##else:
##    print("delete admin account failed")
