import React from 'react';
import './TotalWidget.scss';
import { connect } from "react-redux";
import { injectIntl } from "react-intl";
import { formatNumberWithSettings, getGlobalSettings } from "../utils";

const TotalWidget = (props) => {
  const { intl, settings, data } = props;
  const globalSettings = getGlobalSettings(settings);
  return (<div className={"top-widget-chart"}>
    <h3>{data.measure['translated']}</h3>
    <span className="indicator up"></span>
    <span className="value">{data.total !== null && formatNumberWithSettings('USD', intl, globalSettings, data.total)}
      {data.count !== null && data.count}</span>
  </div>);
}
const mapStateToProps = (state) => {
  return {
    settings: state.getIn(['data', ...['amp-settings'], 'data'])
  }
}
const mapActionCreators = {};

export default connect(mapStateToProps, mapActionCreators)(injectIntl(TotalWidget));
