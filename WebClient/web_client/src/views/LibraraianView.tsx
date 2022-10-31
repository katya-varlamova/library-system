import React from 'react';
import { Formik, Form} from "formik";
import TextField from "./basic/TextField";
import Button from "./basic/Button";
import TableView from "./basic/Table";
import {Grid} from "./basic/Grid";
import RadioButtonList, {RadioOptionType} from "./basic/RadioButtonsList";


interface Props{
    header: string[],
    rows: string[][],
    disabled: boolean,
    message: string,
    initialValues : {
        login: string,
        id : string
    },
    options: RadioOptionType [],
    action : string,
    onChange: (event :any) =>void,
    validationSchema: () => void,
    onClicked: (formValue: { id: string, login: string }) => void
}

const LibrarianView = ({header, rows, onChange, action, options, disabled, message, initialValues, validationSchema, onClicked}: Props) =>{
    return (
        <div className="col-md-12">

            <Formik initialValues={initialValues} validationSchema={validationSchema} onSubmit={onClicked}>
                <Form>
                    <Grid columnsAmount={2}>
                        <TextField flab={"Book ID"} fn={"id"}/>
                        <TextField flab={"User login"} fn={"login"}/>
                        <RadioButtonList options={options} value={action} onChange={onChange}></RadioButtonList>
                        <Button disabled={disabled} lab={"manage!"}></Button>
                        {message && (
                            <div className="form-group">
                                <div className="alert alert-danger" role="alert">
                                    {message}
                                </div>
                            </div>
                        )}
                    </Grid>
                    <TableView header={header} rows={rows}/>
                </Form>
            </Formik>
        </div>
    );
};
export default LibrarianView;