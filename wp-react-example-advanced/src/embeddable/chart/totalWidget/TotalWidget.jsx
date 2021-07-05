import React, { Component } from 'react';
import './TotalWidget.scss';
export default class TotalWidget extends Component {
  render() {
    return <div className={"top-widget-chart"}>
      <h3>Total Disbursements</h3>
      <span className="indicator down"></span>
      <span className="value">94,867,568,000</span>
    </div>;
  }
}
