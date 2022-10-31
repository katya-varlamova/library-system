
import {ErrorMessage, Field} from "formik";
import React from "react";
interface Props {
    fn: string,
    flab: string,
    sec? : boolean
}
const TextField = ({fn, flab, sec} : Props) => {
    return(
        <div className="form-group">
            <label htmlFor={fn}>{flab}</label>
            {(sec) ?
            <Field name={fn} type="password" className="form-control"/> :
                <Field name={fn} type="text" className="form-control"/>}
            <ErrorMessage
                name={fn}
                component="div"
                className="alert alert-danger"
            />
        </div>)
};
export default TextField;