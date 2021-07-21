import React from 'react';
import DataProvider from "../data/DataProvider";
import { Container } from "semantic-ui-react";
import DataConsumer from "../data/DataConsumer";
import TopList from "./TopList";

const TopLists = (props) => {
  const {
    'data-height': height = 500,
    'data-top-type': topType = 'topDonor',
    'data-top-size': topSize = 'top5',
    'data-top-month': topMonth = '36',
    'data-top-currency': topCurrency = 'USD',
    'data-top-FundingType': topFundingType = 'Actual Commitments',
    'data-top-title': topTitle = 'Top Donor',
    'data-top-description': topDescription = 'Top donor description'

  }
    = props;
  const labels = { title: topTitle, description: topDescription };
  const child = (<TopList
    height={height} topType={topType} topSize={topSize} labels={labels} currency={topCurrency} />);
  const newSource = `${topType}/${topSize}/${topMonth}/${topCurrency}`;
  return <DataProvider source={newSource} app={'topLists'} store={newSource} measure={topFundingType}>
    <Container style={{ "height": `${height}px` }} className={"body"} fluid={true}><DataConsumer>
      {child}
    </DataConsumer></Container>

  </DataProvider>
};
export default TopLists;