import React from "react";
import exp from "constants";
import {Grid} from "./Grid";
interface Props{
    data : string[]
};
const TableRow = ({ data}: Props) => {

    return (
        <tr>
                {data.map(item => {
                    return  <td>{item}</td>
                })}
        </tr>
    )
};
// const TableRow = ({ data, header}: Props) => {
//
//     return (
//         header ?
//             <Grid columnsAmount={data.length} >
//             {data.map(item => {
//                 return  <div className={"table__header_cell"}>{item}</div>
//             })}
//             </Grid> :
//             <Grid columnsAmount={data.length} >
//                 {data.map(item => {
//                     return  <div className={"table__cell"}>{item}</div>
//                 })}
//             </Grid>
//     )
// };
export default TableRow;