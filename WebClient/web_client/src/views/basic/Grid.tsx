import styled from 'styled-components'

type GridProps = {
    columnsAmount: number;
    rowHeight?: number;
}

export const Grid = styled.div <GridProps>`
  width: 100%;
  height: 100%;

  display: grid;

  justify-content: center;
  align-items: center;

  grid-template-columns: ${({ columnsAmount }) => `repeat(${columnsAmount}, 1fr)`};
  grid-auto-rows: ${({ rowHeight }) => rowHeight ? `${rowHeight}px` : 'auto'};

`