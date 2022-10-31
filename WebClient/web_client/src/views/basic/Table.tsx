import React from 'react';
import TableRow from "./TableRow";

interface Props{
    header : string[]
    rows : string[][]
};
const TableView = ({ header, rows }: Props) =>{

    return (<div className="containerr">
            <table className="table-scroll">
                <thead>
                <tr>
                    <TableRow data={header}></TableRow>
                </tr>
                </thead>
                <tbody className="body-half-screen">

                        {rows.map(row => {
                            return  <TableRow data={row}></TableRow>
                        })}

                </tbody>
            </table>
            <></>
        </div>

        )
};
// const TableView = ({ header, rows }: Props) =>{
//
// return (
//             <div className={"table"}>
//                 {/*<thead>*/}
//                 {/*<tr>*/}
//                     <TableRow data={header} header={true}></TableRow>
//                 {/*</tr>*/}
//                 {/*</thead>*/}
//
//                 {/*<tbody>*/}
//                 {/*<tr>*/}
//                         {rows.map(row => {
//                             return  <TableRow data={row} header={false}></TableRow>
//                         })}
//                 {/*</tr>*/}
//                 {/*</tbody>*/}
//             </div>)
// };
export default TableView;