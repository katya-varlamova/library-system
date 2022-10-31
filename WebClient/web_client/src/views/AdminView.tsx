import React from 'react';
import { Formik, Form} from "formik";
import TextField from "./basic/TextField";
import Button from "./basic/Button";
import TableView from "./basic/Table";
import {Grid} from "./basic/Grid";
import RadioButtonList, {RadioOptionType} from "./basic/RadioButtonsList";


interface Props{
    lib_header: string[],
    lib_rows: string[][],
    book_header: string[],
    book_rows: string[][],
    disabled: boolean,
    message: string,
    initialValues : {
        book_id: string,
        book_name: string;
        book_author: string,
        lib_id: string,
        lib_name: string,
        lib_address: string
    },
    optionsAction: RadioOptionType [],
    action : string,
    onChangeAction: (event :any) =>void,
    optionsTable: RadioOptionType [],
    table : string,
    onChangeTable: (event :any) =>void,
    validationSchema: () => void,
    onClicked: (formValue: { book_id?: string, book_name?: string; book_author?: string, lib_id?: string, lib_name?: string, lib_address?: string }) => void
}

const AdminView = ({lib_header,lib_rows,book_header,book_rows, optionsAction, optionsTable, action, table, onChangeTable, onChangeAction, disabled, message, initialValues, validationSchema, onClicked}: Props) =>{
    return (
        <div className="col-md-12">

            <Formik initialValues={initialValues} validationSchema={validationSchema} onSubmit={onClicked}>
                <Form>
                    <Grid columnsAmount={2}>
                        <TextField flab={"Book ID"} fn={"book_id"}/>
                        <TextField flab={"Library ID"} fn={"lib_id"}/>
                        <TextField flab={"Book name"} fn={"book_name"}/>
                        <TextField flab={"Library name"} fn={"lib_name"}/>
                        <TextField flab={"Book author"} fn={"book_author"}/>
                        <TextField flab={"Library address"} fn={"lib_address"}/>
                        <RadioButtonList options={optionsAction} value={action} onChange={onChangeAction}></RadioButtonList>
                        <RadioButtonList options={optionsTable} value={table} onChange={onChangeTable}></RadioButtonList>
                        <Button disabled={disabled} lab={"manage!"}></Button>
                        {message && (
                            <div className="form-group">
                                <div className="alert alert-danger" role="alert">
                                    {message}
                                </div>
                            </div>
                        )}
                    </Grid>
                    <Grid columnsAmount={2}>
                        <TableView header={book_header} rows={book_rows}/>
                        <TableView header={lib_header} rows={lib_rows}/>
                    </Grid>
                </Form>
            </Formik>
        </div>
    );
};
export default AdminView;