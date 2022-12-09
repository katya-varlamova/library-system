from faker import Faker
from random import randint
from random import uniform
from random import choice
import csv
MAX_N = 1611

role = ["admin", "librarian", "reader"]
lib_names = []
lib_addresses = []
book_names = []
book_authors = []
def readLibraries():
    global lib_names
    global lib_addresses
    with open('libraries.csv', newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        counter = 0
        for row in reader:
            if counter == MAX_N:
                break
            if counter < 1000:
                lib_names.append('ln1000')
                lib_addresses.append(row['Street Address'].lower())
            elif counter < 1500:
                lib_names.append('ln500')
                lib_addresses.append(row['Street Address'].lower())
            elif counter < 1600:
                lib_names.append('ln100')
                lib_addresses.append(row['Street Address'].lower())
            elif counter < 1610:
                lib_names.append('ln10')
                lib_addresses.append(row['Street Address'].lower())
            elif counter < 1611:
                lib_names.append('ln1')
                lib_addresses.append(row['Street Address'].lower())
            counter += 1


def readBooks():
    global book_names
    global book_authors
    with open('books.csv', newline='', encoding = "ISO-8859-1") as csvfile:
        reader = csv.DictReader(csvfile)
        counter = 0
        for row in reader:
            if counter == MAX_N:
                break
            book_names.append(row['title'].lower())
            book_authors.append(row['authors'].lower())
            counter += 1


    
def generateLibraries():
    faker = Faker()
    f = open('data/library.csv', 'w')
    for i in range(MAX_N):
        line = "{0};{1}\n".format(lib_names[i], lib_addresses[i])
        f.write(line)
    f.close()
    
def generateAdminAccount(acc_id):
    f = open('data/adminaccount.csv', 'a')
    line = "{0}\n".format(acc_id)
    f.write(line)
    f.close()
    
def generateLibrarianAccount(acc_id):
    f = open('data/librarianaccount.csv', 'a')
    lib_id = randint(1, MAX_N - MAX_N // 5)
    line = "{0};{1}\n".format(acc_id, lib_id)
    f.write(line)
    f.close()
    
def generateReaderAccount(acc_id):
    f = open('data/readeraccount.csv', 'a')
    faker = Faker(locale="ru")
    line = "{0};{1}\n".format(acc_id, faker.phone_number())
    f.write(line)
    f.close()
    
def generateAccounts():
    faker = Faker()
    f = open('data/account.csv', 'w')
    logins = [faker.unique.email() for i in range(MAX_N)]
    for i in range(MAX_N):
        r = randint(0, 2)
        if role[r] == "admin":
            generateAdminAccount(i + 1)
        elif role[r] == "librarian":
            generateLibrarianAccount(i + 1)
        else:
            generateReaderAccount(i + 1)
        line = "{0};{1};{2};{3}\n".format(logins[i], faker.password(), faker.first_name(), role[r])
        f.write(line)
    f.close()

def generateBooks():
    f = open('data/book.csv', 'w')
    for i in range(MAX_N):
        line = "{0};{1}\n".format(book_names[i], book_authors[i])
        f.write(line)
    f.close()

def generateBookItems():
    f = open('data/bookitem.csv', 'w')
    for i in range(MAX_N):
        book_id = i + 1
        lib_id = MAX_N - i
        acc_id = randint(1, MAX_N - MAX_N // 5)
        ac = randint(0, 2)
        if ac == 1:
            line = "{0};{1};{2}\n".format(book_id, lib_id, acc_id)
        else:
            line = "{0};{1};\n".format(book_id, lib_id)
        f.write(line)
    f.close()



f = open('data/adminaccount.csv', 'w')
f.close()
f = open('data/readeraccount.csv', 'w')
f.close()
f = open('data/librarianaccount.csv', 'w')
f.close()
readBooks()
readLibraries()

generateBooks()
generateLibraries()
generateAccounts()
generateBookItems()
