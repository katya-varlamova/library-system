import React from 'react';
import RadioButtonList, {RadioOptionType} from "./RadioButtonsList";

export interface Props {
    options: RadioOptionType[];
    onChange: (event : any) => void;
    value : string;
}

const ScrollableList = ({ options, value, onChange}: Props) =>{

    return(
    <div className='container'>
        <div className='scrollable'>
            <div className='content'>
                <RadioButtonList name={"libs"} value={value} onChange={onChange} options={options}></RadioButtonList>
            </div>
        </div>
    </div>)
}

export default ScrollableList;