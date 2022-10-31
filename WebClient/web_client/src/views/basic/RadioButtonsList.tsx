import React from 'react';
import { Field, FieldProps } from 'formik';

export interface RadioButtonProps {
    className?: string | null;
    classNameLabel?: string | null;
    disabled?: boolean;
    id: string;
    label?: string | null;
    labelStyle?: object;
    name?: string;
    style?: object;
    onChange: (event: any) => void;
    value: string;
}


const RadioButtonField: React.FC<RadioButtonProps> = ({
                                                          className,
                                                          classNameLabel,
                                                          disabled,
                                                          id,
                                                          label,
                                                          labelStyle,
                                                          name,
                                                          onChange,
                                                          style,
                                                          value,
                                                      }: RadioButtonProps) => {

        return (
            <React.Fragment>
                <label
                    className={classNameLabel || ''}
                    htmlFor={id}
                    style={labelStyle}
                >
                    <input
                        className={className || ''}
                        checked={id === value}
                        disabled={disabled}
                        id={id}
                        name={name}
                        onChange={onChange}
                        style={style}
                        type="radio"
                        value={id}

                    />
                    {label}
                </label>
            </React.Fragment>

        );
};

RadioButtonField.defaultProps = {
    className: null,
    classNameLabel: null,
    disabled: false,
    label: null,
    labelStyle: {},
    style: {},
};

export interface RadioOptionType {
    id: string;
    label: string;
}

export interface RadioGroupProps {
    className?: string | null;
    classNameLabel?: string | null;
    labelStyle?: object;
    name?: string;
    options: RadioOptionType[];
    style?: object;
    onChange: (event : any) => void;
    value : string;
}

const RadioButtonList: React.FC<RadioGroupProps> = ({
                                                         className,
                                                         classNameLabel,
                                                         labelStyle,
                                                         name,
                                                         options,
                                                         style,
                                                         onChange,
                                                         value
                                                     }: RadioGroupProps) => {
    const displayRadioButtons: React.ReactNode = options.map(({
                                                                  id,
                                                                  label,
                                                              }: RadioOptionType) => (
        <div key={id}>
            <RadioButtonField
                className={className}
                classNameLabel={classNameLabel}
                id={id}
                labelStyle={labelStyle}
                name={name}
                label={label}
                style={style}
                onChange={onChange}
                value={value}
            />
        </div>
    ));

    return (
        <div>
            {displayRadioButtons}
        </div>
    );
};

RadioButtonList.defaultProps = {
    className: null,
    classNameLabel: null,
    labelStyle: {},
    style: {},
};

export default RadioButtonList;