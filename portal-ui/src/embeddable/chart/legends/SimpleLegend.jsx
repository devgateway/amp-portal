import React, { Component, useEffect, useRef } from 'react';
import ReactTooltip from 'react-tooltip';
import PropTypes from 'prop-types';
import './SimpleLegend.scss';
import { getColor } from '../TopChartUtils';

const SimpleLegend = ({ data, toggle, colors, filter }) => {
  let index = 0;
  return (
    <div className="simple-legend">
      <div className="simple-legend-inner">
        <ul>
          {data.map(d => {
            d.index = index;
            const ret = (
              <li key={getColor(d, colors)}>
                  <span
                    className="symbol"
                    style={{
                      border: `2px solid ${getColor(d, colors, filter)}`,
                      backgroundColor: `${getColor(d, colors, filter)}`
                    }}
                    data-tip={d.name}
                    data-for={index.toString()}
                  />
                <span className={`label ${toggle ? 'cursor' : ''}`} data-tip={d.name}
                      data-for={index.toString()}
                      onClick={e => toggle ? toggle(d.id) : null}>
                    {d.name.substring(0, 10)}
                  </span>
                <ReactTooltip place="top" effect="float" backgroundColor={getColor(d, colors, filter)}
                              id={index.toString()} />
              </li>
            );
            index += 1;
            return ret;
          })}
        </ul>
      </div>
    </div>
  );
}

SimpleLegend.propTypes = {
  data: PropTypes.array.isRequired,
  shouldSplitBig: PropTypes.bool,
  formatter: PropTypes.func,
  getColor: PropTypes.func
};
SimpleLegend.defaultProps = {
  shouldSplitBig: false,
  formatter: null,
  getColor: null
};
export default SimpleLegend;
