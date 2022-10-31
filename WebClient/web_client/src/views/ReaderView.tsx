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
        name: string,
        author: string,
        lib_name: string,
        lib_address: string,
    },
    optionsFree: RadioOptionType [],
    free : string,
    onChangeFree: (event :any) =>void,
    validationSchema: () => void,
    onFindClicked: (formValue: { name: string; author: string, lib_name : string, lib_address: string }) => void
}

const ReaderView = ({header, rows, onChangeFree, free, optionsFree, disabled, message, initialValues, validationSchema, onFindClicked}: Props) =>{
    return (
        <div className="col-md-12">

                <Formik initialValues={initialValues} validationSchema={validationSchema} onSubmit={onFindClicked}>
                    <Form>
                        <Grid columnsAmount={2}>
                            <TextField flab={"name"} fn={"name"}/>
                            <TextField flab={"author"} fn={"author"}/>
                            <TextField flab={"library name"} fn={"lib_name"}/>
                            <TextField flab={"library address"} fn={"lib_address"}/>
                            <RadioButtonList options={optionsFree} value={free} onChange={onChangeFree}></RadioButtonList>
                            <Button disabled={disabled} lab={"find!"}></Button>
                        </Grid>
                        <TableView header={header} rows={rows}/>
                        {/*<TableView header={['aheoihjwrjgk wga`gr', 'beohire wghwt hwiug wigh wkjt', 'crwgklwroh jwbgkrgb', 'dwlglgn grnwg`lkw  ']} rows={[['aa rwgr  rwgnl', 'abwrlglnkl', 'ac  gwrgrw', 'adwrg rwgg gwr'], ['bafjqke w`jgkjw`gk kjbewfq qkjFGkejhtqio KQJEGBKJBK', 'bb', 'bc', 'bd Gwkn wGJKN WGk wrgbwjkabkbawkg '], ['ca GWAKJRBJKB kjetankjbgbdzegra aeg', 'cb gkwjrbk grwjgbkrw', 'cc gwjkarkg', 'cdwragjkjkwabakwbgjkw  wrgakb']]}></TableView>*/}
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
    );
};
export default ReaderView;