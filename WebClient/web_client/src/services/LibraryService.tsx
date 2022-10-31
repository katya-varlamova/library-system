import axios from "axios";

import Library from "../models/Library";
import Library_dto from "../dtos/LibrarayDTO";
import API_URL from "../consts/ApiRoute";


class LibraryService {
    dto_to_library(dto: Library_dto) :Library{
        return dto;
    }
    library_to_dto(lib: Library) : Library_dto{
        return lib;
    }
    get(token: string, id? : number, name?: string, address?:string) {
        return axios.get<Library[]>(API_URL + "libraries", {
                headers: {token: token, AccessControlAllowOrigin : '*' },
                params: { id: id, name : name, address: address}
            })
            .then(response => {
                const libs: Library[] = [];
                for (let lib of JSON.parse(JSON.stringify(response.data)).libraries) {
                    libs.push(this.dto_to_library({name : lib.name, address : lib.address, id : lib.id}));
                }
                return libs;
            });
    }
    update(token: string, id : number, lib: Library) {
        return axios
            .put(API_URL + "libraries" + "/" + id.toString(),
                JSON.stringify(this.library_to_dto(lib)),
                {headers: {token: token, AccessControlAllowOrigin : '*', 'Content-Type': 'application/json', Accept: 'application/json' }})
            .then(response => {
               return response.status
            })
    }
    post(token: string, lib: Library) {
        return axios
            .post(API_URL + "libraries",
                JSON.stringify(this.library_to_dto(lib)),
                {headers: {token: token, AccessControlAllowOrigin : '*', 'Content-Type': 'application/json', Accept: 'application/json'}})
            .then(response => {
                return response.status
            })
    }
    delete(token: string, id : number) {
        return axios
            .delete(API_URL + "libraries" + "/" + id.toString(), {
                headers: {token: token, AccessControlAllowOrigin : '*', 'Content-Type': 'application/json', Accept: 'application/json' }
            })
            .then(response => {
                return response.status
            })
    }
}

export default new LibraryService();
