import React from 'react';
import DataProvider from "../data/DataProvider";
import { Container } from "semantic-ui-react";
import DataConsumer from "../data/DataConsumer";
import TopList from "./TopList";

const TopLists = (props) => {
    const {
      'data-height': height = 500,
      'data-top-type': topType = 'topDonors',
      'data-top-size': topSize = 'top5',
      'data-top-month': topMonth = '36',
      'data-top-currency': topCurrency = 'USD',
      'data-top-FundingType': topFundingType = 'Actual Commitments',
      'data-top-title': topTitle = 'Top Donor',
      'data-top-description': topDescription = 'Top donor description',
      'data-top-show-donor-group': topShowDonorGroupStr = 'false',
      'data-top-tooltip': topTooltip,
      locale

    }
      = props;
    const topShowDonorGroup = topShowDonorGroupStr === 'true';
    const labels = { title: topTitle, description: topDescription, tooltip: topTooltip };
    const fields = [];
    const numberFields = [];
    const numberFieldsFormatted = [];
    const linkFields = [];
    let identity;
    if (topType === 'topDonors') {
      if (topShowDonorGroup) {
        fields.push('donor-group');
        identity = 'donor-group';
      } else {
        fields.push('donor-agency');
        identity = 'donor-agency';
      }
      fields.push('actual-commitments');
      numberFieldsFormatted.push('actual-commitments');
    } else {
      if (topType === 'topProjects') {
        identity = 'project-title';
        if (topSize === "top10") {
          fields.push('actual-start-date');
          fields.push("donor-agency")
          fields.push("primary-sector")
          fields.push('project-title');
          fields.push('actual-commitments');
          fields.push('actual-disbursements');
        } else {
          fields.push('project-title');
          fields.push("donor-agency");
          fields.push('actual-commitments');
        }
      } else {
        identity = 'project-title';
        if (topType === 'topUpdatedProjects') {
          if (topSize === "top10") {
            fields.push('actual-start-date');
            fields.push('project-title');
            fields.push("donor-agency");
          } else {
            fields.push('project-title');
            fields.push('actual-start-date');
            fields.push('actual-commitments');
          }
        }


      }
      linkFields.push('project-title');
      numberFields.push('actual-commitments');


    }

    const child = (<TopList
      height={height} topType={topType} topSize={topSize} labels={labels} currency={topCurrency} fields={fields}
      topShowDonorGroup={topShowDonorGroup} numberFields={numberFields} linkFields={linkFields} identity={identity}
      isBigTable={topSize === "top10"} numberFieldsFormatted={numberFieldsFormatted} />);
    const newSource = `${topType}/${topSize}/${topMonth}/${topCurrency}/${topShowDonorGroup}`;
    return <DataProvider source={newSource} app={'topLists'} store={newSource} measure={topFundingType} locale={locale}>
      <Container style={{ "height": `${height}px` }} className={"body"} fluid={true}><DataConsumer>
        {child}
      </DataConsumer></Container>

    </DataProvider>
  }
;
export default TopLists;