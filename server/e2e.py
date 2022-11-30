import requests
import unittest

class TestMain(unittest.TestCase):
  
  def test_login(self):
    headers = {'login': 'hashley@bailey-phillips.info', 'password': 'SL_90EXmH#', 'Content-type': 'application/json', 'Accept': 'text/'}
    r = requests.get("https://localhost:8000//api/v2/accounts",
                 headers=headers, verify=False)

    self.assertEqual(r.json()['id'], 1)
  def test_get_books(self):
    headers = {'login': 'hashley@bailey-phillips.info', 'password': 'SL_90EXmH#', 'Content-type': 'application/json', 'Accept': 'text/'}
    r = requests.get("https://localhost:8000//api/v2/accounts",
                 headers=headers, verify=False)
    token = r.json()['token']
    headers = {'token': token, 'Content-type': 'application/json', 'Accept': 'text/'}
    params = {'author' : 'j.k. rowling'}
    r = requests.get("https://localhost:8000//api/v2/books",
                 headers=headers, params = params, verify=False)
    self.assertEqual(len(r.json()['books']), 4)

  def test_get_libs(self):
    headers = {'login': 'hashley@bailey-phillips.info', 'password': 'SL_90EXmH#', 'Content-type': 'application/json', 'Accept': 'text/'}
    r = requests.get("https://localhost:8000//api/v2/accounts",
                 headers=headers, verify=False)
    token = r.json()['token']
    headers = {'token': token, 'Content-type': 'application/json', 'Accept': 'text/'}
    params = {'address' : '101 first street'}
    r = requests.get("https://localhost:8000//api/v2/libraries",
                 headers=headers, params = params, verify=False)
    self.assertEqual(len(r.json()['libraries']), 1)


if __name__ == "__main__":
  unittest.main()

