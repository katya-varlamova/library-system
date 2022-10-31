import React from 'react';
import { Formik, Form} from "formik";
import TextField from "./basic/TextField";
import Button from "./basic/Button";


interface Props{
    disabled: boolean,
    message: string,
    initialValues : {
        username: string,
        password: string,
    },
    validationSchema: () => void,
    onLoginClicked: (formValue: { username: string; password: string }) => void
}

const LoginView = ({ disabled, message, initialValues, validationSchema, onLoginClicked}: Props) =>{

    return (
        <div className="col-md-12">
            <div className="card card-container">
                <img
                    src="//ssl.gstatic.com/accounts/ui/avatar_2x.png"
                    alt="profile-img"
                    className="profile-img-card"
                />

                <Formik initialValues={initialValues} validationSchema={validationSchema} onSubmit={onLoginClicked}>
                    <Form>
                        <TextField flab={"Login"} fn={"username"}/>
                        <TextField flab={"Password"} fn={"password"} sec={true}/>
                        <Button disabled={disabled} lab={"Login"}></Button>
                        {message && (
                            <div className="form-group">
                                <div className="alert alert-danger" role="alert">
                                    {message}
                                </div>
                            </div>
                        )}
                    </Form>
                </Formik>
            </div>
        </div>
    );
};
export default LoginView;