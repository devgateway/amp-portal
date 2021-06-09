import React, { useState } from "react";
import { Button, Container, Grid } from "semantic-ui-react";
import DataProvider from "../../data/DataProvider";
import { connect } from "react-redux";
import Bar from "../../charts/Bar";
import DataConsumer from "../../data/DataConsumer";
import { buildBarOptions, buildDivergingOptions, buildPieOptions, buildTopsData } from './chartOptionsBuilder'
import './charts.scss'
import TopPie from "../../charts/TopPie";
import TheContent from "../../wp/template-parts/TheContent";
import Top from "../../charts/Top";
import DonorScoreCard from "../../charts/donorScorecard/DonorScoreCard";
import { useIntl } from 'react-intl'
import TopList from "../../charts/TopList/TopList";
import LoginWidget from "../../charts/login/LoginWidget";
import TotalWidget from "../../charts/totalWidget/TotalWidget";

const BarChar = (props) => {
  const intl = useIntl();
  const { data } = props
  const options = buildBarOptions(data, true, intl);
  return <Bar {...props} options={options}
              format={{ style: "percent", currency: "EUR" }} />
}
const TopChart = (props) => {
  const { data, legends, colors, height, groupMode } = props
  const options = buildTopsData(data)
  return <Top groupMode={groupMode} height={height} legends={legends} colors={colors} options={options}
              format={{ style: "percent", currency: "EUR" }} />
}

const PieChart = (props) => {
  const { data, legends, colors, height, measure } = props
  const options = buildTopsData(data, true)
  return <TopPie height={height} legends={legends} colors={colors} options={options} measure={measure}
                 format={{ style: "percent", currency: "EUR" }} />
}

const DonorScoreCardChart = (props) => {
  return <DonorScoreCard />;
}

const TopListsChart = (props) => {
  return <TopList />;
}

const LoginWidgetComponent = (props) => {
  return <LoginWidget />;
}
const Diverging = (props) => {
  const { data, legends, colors, height } = props
  const options = buildDivergingOptions(data, true)
  return <Diverging height={height} legends={legends} colors={colors} options={options}
                    format={{ style: "percent", currency: "EUR" }} />
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
    'data-group-mode': groupMode = 'grouped',
    'data-legends-left': left = 'Left Legend',
    'data-legends-bottom': bottom = 'Bottom Legend',
    'data-dualmode': dualMode,

    'data-legend-position': legendPosition = "right",
    'data-show-legends': showLegends = "true",

    'data-chart-title': title = "Chart title",
    'data-chart-data-source': dataSource = "Data Source",

    'data-toggle-info-label': toggleInfoLabel = "Info Graphic",
    'data-toggle-chart-label': toggleChartLabel = "Chart",
    'data-params': params = '{}',
    'data-number-format': format = '{"style":"percent", "minimumFractionDigits": 1, "maximumFractionDigits": 1}',
    'data-tick-rotation': tickRotation = 0,
    'data-tick-color': tickColor = "rgb(92,93,99)",
    'data-keys': keys = null,
    'data-style': style = "decimal",
    "data-decimals": decimals = "2",
    'data-currency': currency = "",
    'data-chart-measure': measure = "Actual Commitments",
    'data-chart-date-from': dateFrom = "2010",
    'data-chart-date-to': dateTo = "2030"
  } = props;
  let newSource = source;
  const itemWidth = props["data-legends-width"] ? parseInt(props["data-legends-width"]) : 180
  const [mode, setMode] = useState(editing ? "chart" : 'info')
  const legends = {
    title,
    left
  };
  const colors = {
    scheme: scheme,
    colorBy: 'keys'
  }
  let child = null;
  if (app === 'top') {
    const contentHeight = (editing ? height - 180 : height - 60);
    if (type === 'bar') {
      child =
        <TopChart height={contentHeight} legends={legends} colors={colors} groupMode={groupMode}></TopChart>;
    } else {
      child = <PieChart height={contentHeight} legends={legends} colors={colors} groupMode={groupMode} />;
    }
  }
  if (app === 'donorScoreCard') {
    child = <DonorScoreCardChart />
  }
  if (app === 'topList') {
    child = <TopListsChart />
  }
  if (app === 'totalWidget') {
    child = <TotalWidget />;
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
          groupMode: groupMode,
          measure
        }
        child =
          <BarChar {...chartProps} ></BarChar>
      } else {
        child = <h1>Soon</h1>;
      }
    }
  }
  const dual = (dualMode === 'true')
  const dateFilter = {};
  dateFilter.from = dateFrom;
  dateFilter.to = dateTo;

  return <Container className={"chart container"} fluid={true}>

    <DataProvider store={newSource.split("/")} source={newSource} app={app} measure={measure} dateFilter={dateFilter}>

      {(!dual || mode == 'chart') &&
      <Container style={{ "height": `${height}px` }} className={"body"} fluid={true}><DataConsumer>
        {child}
      </DataConsumer></Container>}

    </DataProvider>

    {dual && childContent && mode == 'info' && <Container className={"body"}>
      <TheContent post={{ content: { rendered: childContent } }}></TheContent>
    </Container>}

    {!editing && dual && <Grid className={"footnote"}>
      <Grid.Column width={1}></Grid.Column>
      <Grid.Column width={7}>
        <Button className={(mode === 'info') ? "active" : ""}
                onClick={e => setMode('info')}>{toggleInfoLabel}</Button> |
        <Button className={(mode === 'chart') ? "active" : ""}
                onClick={e => setMode('chart')}>{toggleChartLabel}</Button>
      </Grid.Column>
      <Grid.Column width={8}></Grid.Column>
    </Grid>}
  </Container>
}


const mapStateToProps = (state, ownProps) => {
  return {}
}

const mapActionCreators = {};

export default connect(mapStateToProps, mapActionCreators)(Chart)