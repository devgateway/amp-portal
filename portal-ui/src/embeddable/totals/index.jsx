import React, { Component } from 'react';
import { Container, Button, Table, Menu, Icon, Popup } from "semantic-ui-react";
import './Totals.scss';

class Totals extends Component {
  componentDidMount() {

  }

  render() {
    return (
    <Container fluid className={"totals"}>
    <Table unstackable>
  <Table.Header>
    <Table.Row>
      <Table.HeaderCell></Table.HeaderCell>
      <Table.HeaderCell>Actual Commitments</Table.HeaderCell>
      <Table.HeaderCell>Actual Disbursements</Table.HeaderCell>
    </Table.Row>
  </Table.Header>

  <Table.Body>
    <Table.Row>
      <Table.Cell>Totals (USD)</Table.Cell>
      <Table.Cell>572,940,493</Table.Cell>
      <Table.Cell>422,250,469</Table.Cell>
    </Table.Row>
  </Table.Body>

</Table>

    </Container>)
  }
}


export default Totals
