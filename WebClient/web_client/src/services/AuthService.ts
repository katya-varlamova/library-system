import axios from "axios";
import Account from "../models/Account";
import Account_dto from "../dtos/AccountDTO";
import API_URL from "../consts/ApiRoute";



class AuthService {
  dto_to_acc(dto: Account_dto, login : string) :Account{
    return {
      name : dto.name,
      admin_acc : {},
      reader_acc : {phone : dto.reader_acc?.phone},
      librarian_acc : {lib_id : dto.librarian_acc?.lib_id},
      token : dto.token,
      id :dto.id,
      login : login
    };
  }
  acc_to_dto(acc: Account) : Account_dto{
    return {
      name : acc.name,
      admin_acc : {},
      reader_acc : {phone : acc.reader_acc?.phone},
      librarian_acc : {lib_id : acc.librarian_acc?.lib_id},
      token : acc.token,
      id :acc.id
    };
  }
  _login(username: string, password: string) {

    return axios
        .get(API_URL + "accounts", {
          headers: {login: username, password: password, AccessControlAllowOrigin : '*' }
        })
        .then(response => {
          const data = JSON.parse(JSON.stringify(response.data));
          return this.dto_to_acc(data, username);
        });
  }
  login(username: string, password: string) {
    // alert(username + " " + password);
    return axios

        .get(API_URL + "accounts", {
          headers: {login: username, password: password, AccessControlAllowOrigin : '*' }
        })
        .then(response => {
          // alert("RESP:" + username + " " + password);
          const data = JSON.parse(JSON.stringify(response.data));
          const acc  = this.dto_to_acc(data, username);

          if (JSON.parse(JSON.stringify(response.data)).token) {
            localStorage.setItem("user", JSON.stringify(acc));
          }
          return acc;
        });
  }

  logout() {
    localStorage.removeItem("user");
  }

  register(login: string, password: string, role: string, acc: Account) {
    return axios.post(API_URL + "accounts",
        JSON.stringify(this.acc_to_dto(acc)),
        { headers: {login: login, password: password, role: role , 'Content-Type': 'application/json', Accept: 'application/json'}},
    );
  }

  getCurrentUser() : Account | null{
    const userStr = localStorage.getItem("user");
    if (userStr) return JSON.parse(userStr);

    return null;
  }
}

export default new AuthService();
