import React, { Component } from 'react';
import './DonorScoreCard.scss';
import Top from "../Top";

const DonorScoreCard = (props) => {
  const { legends } = props;
  return (<div className={"donor-scorecard-chart"}>
    <h3>{legends.title}</h3>
    <div className="description">{legends.chartDescription}
    </div>
    <div className="data-wrapper">
      <Top layout={"horizontal"} showLegend={false} isDonorScoreCard={true}
           padding={0.45} {...props} />
    </div>
  </div>)
}
export default DonorScoreCard;
