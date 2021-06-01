import React, { Component } from 'react';
import './DonorScoreCard.scss';
export default class DonorScoreCard extends Component {
  render() {
    return <div className={"donor-scorecard-chart"}>
      <h3>Donor Score Card</h3>
      <div className="description">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam sit amet lectus ut neque blandit ultricies.</div>
      <div className="data-wrapper">
        <div className="data-item">
          <span className="label">On-Time</span>
          <div className="chart-wrapper">chart goes here</div>
        </div>
        <div className="data-item">
          <span className="label">Late</span>
          <div className="chart-wrapper">chart goes here</div>
        </div>
        <div className="data-item">
          <span className="label">No Updates</span>
          <div className="chart-wrapper">chart goes here</div>
        </div>
      </div>
    </div>;
  }
}
