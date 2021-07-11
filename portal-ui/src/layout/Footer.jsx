import React, { Component } from "react";
import { Container, Grid } from "semantic-ui-react";

import { Page, PageConsumer, PageProvider } from "@devgateway/wp-react-lib";
import './Footer.scss';

class Footer extends Component {
  componentDidMount() {

  }

  render() {
    return (<Container fluid className={"amp footer"}>
      <PageProvider slug={"footer"} store={"footer"}>
        <PageConsumer>
          <Page></Page>
        </PageConsumer>
      </PageProvider>

    </Container>)
  }
}


export default Footer

const DefaultFooter = () => {
  //TODO Default Footer needs to be style better
  return (
    <Container fluid className={"default footer"}>
      <Grid>
        <Grid.Column computer={4} mobile={16}><p>Development Gateway <img className={"haiti-img"}
                                                                          src={"/img/haiti.png"}
                                                                          alt="Country Logo" /> Haiti |</p>
        </Grid.Column>
        <Grid.Column computer={8} mobile={16}><p>Contact us @ info@developmentgateway.org</p></Grid.Column>
        <Grid.Column computer={4} mobile={16}><img alt={"DG logo"} className={"dg-logo"} src={"/img/DG_logo.png"} /><img
          alt={"Funder logo"} className={"usaid-logo"} src={"/img/usaidLogo.png"} />
        </Grid.Column>
      </Grid>
    </Container>)
};
