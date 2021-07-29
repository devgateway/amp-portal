import React, { Component } from 'react';
import { Container, Button, Table, Menu, Icon, Popup } from "semantic-ui-react";
import './Totals.scss';
import { connect } from "react-redux";
import { injectIntl } from "react-intl";
import { formatNumberWithSettings, getGlobalSettings } from "../chart/utils";

const Totals = ({ data, settings, intl }) => {
  const globalSettings = getGlobalSettings(settings);
  return (
    <Container fluid className={"totals"}>
      <Table unstackable>
        <Table.Header>
          <Table.Row>
            <Table.HeaderCell></Table.HeaderCell>
            <Table.HeaderCell>{data.headers['actual-commitments']}</Table.HeaderCell>
            <Table.HeaderCell>{data.headers['actual-disbursements']}</Table.HeaderCell>
          </Table.Row>
        </Table.Header>
        <Table.Body>
          <Table.Row>
            <Table.Cell>Totals ({data['Currency']})</Table.Cell>
            <Table.Cell>{formatNumberWithSettings(null, intl, globalSettings, data.totals['Total Actual Commitments'])}</Table.Cell>
            <Table.Cell>{formatNumberWithSettings(null, intl, globalSettings, data.totals['Total Actual Disbursements'])}</Table.Cell>
          </Table.Row>
        </Table.Body>
      </Table>
    </Container>);
}
const mapStateToProps = (state) => {
  return {
    settings: state.getIn(['data', ...['amp-settings'], 'data'])
  }
}
const mapActionCreators = {};

export default connect(mapStateToProps, mapActionCreators)(injectIntl(Totals));
