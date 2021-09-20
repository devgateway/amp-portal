import React, { useState } from "react";
import { Button, Container, Grid } from "semantic-ui-react";
import DataProvider from "../data/DataProvider";
import { connect } from "react-redux";
import Bar from "./Bar";
import DataConsumer from "../data/DataConsumer";
import {
  buildBarOptions,
  buildDonorScoreCardOptions,
  buildTopsData, buildTotalWidgetOptions
} from './chartOptionsBuilder'
import './charts.scss'
import TopPie from "./TopPie";
import Top from "./Top";
import DonorScoreCard from "./donorScorecard/DonorScoreCard";
import { injectIntl, useIntl } from 'react-intl'
import LoginWidget from "./login/LoginWidget";
import TotalWidget from "./totalWidget/TotalWidget";

const BarChar = (props) => {
  const intl = useIntl();
  const { data } = props
  const options = buildBarOptions(data, intl);
  return <Bar {...props} options={options} />
}
const TopChart = (props) => {
  const { data, legends, colors, height, groupMode, barHeight } = props
  const options = buildTopsData(data)
  return <Top groupMode={groupMode} height={height} legends={legends} colors={colors} options={options}
              barHeight={barHeight}
              format={{ style: "percent", currency: "EUR" }} />
}

const PieChart = (props) => {
  const { data, legends, colors, height, measure, pieHeight } = props
  const options = buildTopsData(data)
  return <TopPie height={height} legends={legends} colors={colors} options={options} measure={measure}
                 pieHeight={pieHeight}
                 format={{ style: "percent", currency: "EUR" }} />
}

const DonorScoreCardChart = (props) => {
  const { data } = props
  const options = buildDonorScoreCardOptions(data);
  return <DonorScoreCard {...props} options={options}
                         format={{ style: "percent", currency: "EUR" }} />;
}

const TotalsWidgetComponent = (props) => {
  const { data } = props
  const options = buildTotalWidgetOptions(data);
  return <TotalWidget {...props} options={options} />;
}
const LoginWidgetComponent = (props) => {
  return <LoginWidget />;
}


const Chart = (props) => {
  const { filters } = props
  const {
    parent,
    "data-editing": editing = false,
    unique,
    childContent,
    "data-app": app = "funding",
    "data-height": height = 500,
    "data-chart-type": type = 'bar',
    'data-source': source = 'ftype',
    'data-color-by': colorBy = 'index',
    'data-color-scheme': scheme = 'nivo',
    'data-group-mode': defaultGroupMode = 'grouped',
    'data-legends-left': left = 'Left Legend',
    'data-legends-bottom': bottom = 'Bottom Legend',
    'data-dualmode': dualMode,

    'data-legend-position': legendPosition = "right",
    'data-show-legends': showLegends = "true",

    'data-chart-title': title = "Chart title",
    'data-chart-description': chartDescription = "Chart description",

    'data-toggle-info-label': toggleInfoLabel = "Info Graphic",
    'data-toggle-chart-label': toggleChartLabel = "Chart",
    'data-params': params = '{}',
    'data-number-format': format = '{"style":"percent", "minimumFractionDigits": 1, "maximumFractionDigits": 1}',
    'data-tick-rotation': tickRotation = 0,
    'data-tick-color': tickColor = "rgb(255,255,255)",
    'data-tick-color': tickFontColor = "rgb(92,93,99)",
    'data-keys': keys = null,
    'data-style': style = "decimal",
    "data-decimals": decimals = "2",
    'data-currency': currency = "",
    'data-chart-measure': measure = "Actual Commitments",
    'data-chart-date-from': dateFrom = "2010",
    'data-chart-date-to': dateTo = "2030",
    'data-chart-amp-on-time': onTime = 'On time',
    'data-chart-amp-on-time-tooltip': onTimeTooltip = 'Donor has updated projects within the quarter (not during validation period)',
    'data-chart-amp-validation': validation = 'Validation period',
    'data-chart-amp-validation-tooltip': validationTooltip = 'Donor has updated projects within the validation period for the specified quarter',
    'data-chart-amp-late': late = 'Late',
    'data-chart-amp-late-tooltip': lateTooltip = 'Donor did not update any projects within the quarter',
    'data-chart-amp-no-updates': noUpdate = 'No Updates',
    'data-chart-amp-no-updates-tooltip': noUpdateTooltip = 'Donor was configured as “Donor with no updates” within the quarter',
    'data-chart-amp-size': ampSize = 11,
    locale,
    intl
  } = props;
  let newSource = source;
  const itemWidth = props["data-legends-width"] ? parseInt(props["data-legends-width"]) : 180
  const legends = {
    title,
    left,
    chartDescription
  };
  const colors = {
    scheme: scheme,
    colorBy: 'keys'
  }
  let child = null;
  if (app === 'top') {

    const chartHeight = `${height - (editing ? 86 + 15 : 86)}px`;
    if (type === 'bar') {
      child =
        <TopChart height={height} legends={legends} colors={colors} groupMode={defaultGroupMode}
                  barHeight={chartHeight}></TopChart>;
    } else {
      child =
        <PieChart height={height} legends={legends} colors={colors} groupMode={defaultGroupMode}
                  pieHeight={chartHeight} />;
    }
  }
  if (app === 'donorScoreCard') {
    const contentHeight = (editing ? height - 100 : height);
    legends.scoreCardLegends = {}
    legends.scoreCardLegends['amp.on-time'] = { label: onTime, tooltip: onTimeTooltip };
    legends.scoreCardLegends['amp.validation'] = { label: validation, tooltip: validationTooltip };
    legends.scoreCardLegends['amp.late'] = { label: late, tooltip: lateTooltip };
    legends.scoreCardLegends['amp.no-updates'] = { label: noUpdate, tooltip: noUpdateTooltip };
    legends.scoreCardLegendsSize = ampSize;

    child = <DonorScoreCardChart barHeight={80} legends={legends} colors={colors} groupMode={defaultGroupMode} />
  }
  if (app === 'totalWidget') {
    const { 'data-chart-measure': measure = "Actual Commitments" } = props;
    newSource = newSource + '/' + measure;
    child = <TotalsWidgetComponent measure={measure} />;
  }
  if (app === 'login') {
    child = <LoginWidget />;
  } else {
    const contentHeight = (editing ? height - 100 : height);
    if (app === 'funding') {
      if (type === 'bar') {
        const chartProps = {
          tickColor: decodeURIComponent(tickColor),
          tickRotation: tickRotation,
          showLegends: showLegends == "true",
          itemWidth: itemWidth,
          height: `${contentHeight}px`,
          legendPosition: legendPosition,
          legends: legends,
          colors: colors,
          defaultGroupMode: defaultGroupMode,
          measure
        }
        child =
          <BarChar {...chartProps} ></BarChar>
      } else {
        child = <h1>Soon</h1>;
      }
    }
  }
  const dateFilter = {};
  dateFilter.from = dateFrom;
  dateFilter.to = dateTo;
  return <Container className={"chart container"} fluid={true}>
    <DataProvider store={newSource.split("/")} source={newSource} app={app} measure={measure}
                  dateFilter={dateFilter} locale={locale}>
      <Container style={{ "height": `${height}px` }} className={"body"} fluid={true}><DataConsumer>
        {child}
      </DataConsumer></Container>
    </DataProvider>
  </Container>
}


const mapStateToProps = (state, ownProps) => {
  return {}
}

const mapActionCreators = {};

export default connect(mapStateToProps, mapActionCreators)(injectIntl(Chart))