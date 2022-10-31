import React from "react";
interface Props {
    disabled: boolean,
    lab: string,
}
const Button = ({disabled, lab} : Props) => {
    return(
        <div className="form-group">
            <button type="submit" className="btn btn-primary btn-block" disabled={disabled}>
                {disabled && (
                    <span className="spinner-border spinner-border-sm"></span>
                )}
                <span>{lab}</span>
            </button>
        </div>)
};
export default Button;
