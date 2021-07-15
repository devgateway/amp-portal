import React, { Component } from 'react';
import PropTypes from 'prop-types';
import './ToolTip.scss';
import * as d3 from 'd3-format';
import { formatNumberWithSettings, getGlobalSettings } from "../utils";
import { injectIntl } from "react-intl";
import { connect } from "react-redux";


const ToolTip = ({
                   titleLabel,
                   color,
                   value,
                   total,
                   minWidth,
                   isYearTotal,
                   settings,
                   intl,
                   currencyCode,
                   amountsIn = true
                 }) => {
  const getActualWidth = (inputText) => {
    const font = '16px times new roman';
    const canvas = document.createElement('canvas');
    const context = canvas.getContext('2d');
    context.font = font;
    const { width } = context.measureText(inputText);
    return Math.ceil(width);
  }
  const globalSettings = getGlobalSettings(settings);
  const percentage = total > 0 ? (value * 100) / total : 0;
  const headerStyle = { backgroundColor: color };
  const containerStyle = {};
  // Dont make it wider if the content doesnt need it.
  if (minWidth && getActualWidth(titleLabel) > minWidth) {
    containerStyle.minWidth = minWidth;
  }
  return (
    <div className="generic-tooltip" style={containerStyle}>
      <div className="tooltip-header tooltip-color" style={headerStyle}>
        {titleLabel}
      </div>
      <div className="inner">
        <div className="">
          <div className="element">
              <span className="formattedValue">
                {formatNumberWithSettings(currencyCode, intl, globalSettings, value)}
                {globalSettings.numberDividerDescriptionKey && amountsIn ? ` (${intl.formatMessage({
                  id: `amp.chart.dashboard:${globalSettings.numberDividerDescriptionKey}`
                })})` : ' %'}
              </span>
          </div>
          {percentage > 0 ? (
            <div className="element grey">
                <span className="of-total">
                  {formatNumberWithSettings('', intl, globalSettings, percentage)}
                  <b>% </b>
                  {isYearTotal
                    ? intl.formatMessage({ id: 'amp.chart.dashboard:of-year-total', defaultMessage: "of Year Total" })
                    : intl.formatMessage({ id: 'amp.chart.dashboard:of-total', defaultMessage: "of Total" })}
                </span>
            </div>
          ) : null}
        </div>
      </div>
    </div>
  );
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
const mapStateToProps = (state) => {
  return {
    settings: state.getIn(['data', ...['amp-settings'], 'data'])
  }
}
const mapActionCreators = {};

export default connect(mapStateToProps, mapActionCreators)(injectIntl(ToolTip));

