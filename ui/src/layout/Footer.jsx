import React, { Component } from "react";
import { Container, Grid } from "semantic-ui-react";
import './footer.scss'
import PageProvider from "../wp/providers/PageProvider";
import PageConsumer from "../wp/consumers/PageConsumer";
import WPContent from "../wp/WPContent";
import { Page } from "../wp";

class Footer extends Component {
  componentDidMount() {

  }

  render() {
    //TODO as per @sebas suggestion we will change the way we provide the fallback component
    return (
      <Container fluid className={"amp footer"}>
        <PageProvider slug={"footer"} store={"footer"} fallbackComponent={<DefaultFooter />}>
          <PageConsumer>
            <WPContent {...this.props} defaultTemplate={Page} />
          </PageConsumer>
        </PageProvider>
      </Container>
    );
  }
}

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
}

export default Footer
