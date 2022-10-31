import React from "react";

import {Form, Formik} from "formik";

import TextField from "./basic/TextField";
import RadioButtonGroup, {RadioOptionType} from "./basic/RadioButtonsList";
import ScrollableList from "./basic/ScrollableList";

interface Props{
    successful: boolean,
    message: string,
    initialValues : {
        login: string,
        pwd: string,
        phone: string,
        name : string
    },
    validationSchema: () => void,
    onRegisterClicked: (form: {login: string, pwd: string, phone: string, name : string}) => void,
    lib_id: string,
    onChangeLibrary: (event :any) =>void,
    onChangeRole: (event :any) =>void,
    role : string,
    optionsLibs: RadioOptionType [],
    optionsRole: RadioOptionType []
}

const RegistrationView = ({ successful, message, initialValues, validationSchema, onRegisterClicked, lib_id, role, onChangeRole, onChangeLibrary, optionsRole, optionsLibs}: Props) =>{

    return (
        <div className="col-md-12">
            <div className="card card-container">
                <img
                    src="//ssl.gstatic.com/accounts/ui/avatar_2x.png"
                    alt="profile-img"
                    className="profile-img-card"
                />

                <Formik
                    initialValues={initialValues}
                    validationSchema={validationSchema}
                    onSubmit={onRegisterClicked}
                >
                    <Form>
                        {!successful && (
                            <div>
                                <TextField fn={"login"} flab={"login"}/>
                                <TextField fn={"pwd"} flab={"password"}/>
                                <TextField fn={"name"} flab={"name"}/>

                                <RadioButtonGroup name={"role"} options={optionsRole} onChange={onChangeRole} value={role}></RadioButtonGroup>
                                {(role == "reader") ?
                                    <div>
                                    <TextField fn={"phone"} flab={"phone"}/>
                                    </div> : null
                                }

                                {(role == "librarian") ?
                                    <div>
                                    <ScrollableList options={optionsLibs} onChange={onChangeLibrary} value={lib_id}></ScrollableList>
                                    </div> : null
                                }

                                <div className="form-group">
                                    <button type="submit" className="btn btn-primary btn-block">Sign Up</button>
                                </div>
                            </div>
                        )}

                        {message && (
                            <div className="form-group">
                                <div
                                    className={
                                        successful ? "alert alert-success" : "alert alert-danger"
                                    }
                                    role="alert"
                                >
                                    {message}
                                </div>
                            </div>
                        )}
                    </Form>
                </Formik>
            </div>
        </div>
    );
}
export default RegistrationView