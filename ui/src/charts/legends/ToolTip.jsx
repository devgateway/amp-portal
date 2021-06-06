import React, { Component } from 'react';
import PropTypes from 'prop-types';
import './ToolTip.scss';
import { formatNumberWithSettings } from "../utils";
import { injectIntl } from "react-intl";


class ToolTip extends Component {
  // eslint-disable-next-line class-methods-use-this
  getActualWidth(inputText) {
    const font = '16px times new roman';
    const canvas = document.createElement('canvas');
    const context = canvas.getContext('2d');
    context.font = font;
    const { width } = context.measureText(inputText);
    return Math.ceil(width);
  }

  render() {
    const {
      titleLabel, color, value, total, minWidth, isYearTotal, globalSettings, intl
    } = this.props;
    const percentage = total > 0 ? (value * 100) / total : 0;
    const headerStyle = { backgroundColor: color };
    const containerStyle = {};
    // Dont make it wider if the content doesnt need it.
    if (minWidth && this.getActualWidth(titleLabel) > minWidth) {
      containerStyle.minWidth = minWidth;
    }
    return (
      <div className="generic-tooltip" style={containerStyle}>
        <div className="tooltip-header" style={headerStyle}>
          {titleLabel}
        </div>
        <div className="inner">
          <div className="">
            <div className="element">
              <span className="formattedValue">
                {formatNumberWithSettings('USD', intl, globalSettings, value)}
              </span>
            </div>
            {percentage > 0 ? (
              <div className="element grey">
                <span className="of-total">
                  {formatNumberWithSettings('', intl, globalSettings,
                    percentage)}
                  <b>% </b>
                  {isYearTotal
                    ? intl['amp.ndd.dashboard:of-year-total']
                    : intl['amp.ndd.dashboard:of-total']}
                </span>
              </div>
            ) : null}
          </div>
        </div>
      </div>
    );
  }
}

ToolTip.propTypes = {
  titleLabel: PropTypes.string.isRequired,
  color: PropTypes.string.isRequired,
  value: PropTypes.number.isRequired,
  formattedValue: PropTypes.number,
  total: PropTypes.number.isRequired,
  minWidth: PropTypes.number,
  isYearTotal: PropTypes.bool,
  globalSettings: PropTypes.object.isRequired
};

ToolTip.defaultProps = {
  minWidth: null,
  isYearTotal: false,
  formattedValue: 0
};

export default injectIntl(ToolTip);
