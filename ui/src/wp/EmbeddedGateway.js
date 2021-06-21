import React from 'react'
import ReactDOM from 'react-dom'


import asyncComponent from "../AsyncComponent";
import {Provider} from "react-redux";
import getStore from "../redux/store";
import {injectIntl, IntlProvider} from "react-intl";
import messages_en from "../translations/en.json";
import Chart from "../embeddable/chart/index";
import Filter from "../embeddable/filter";
import Map from "../embeddable/map/index";


const TabbedPosts = asyncComponent(() => import("../embeddable/tabbedposts/"));
const PostsCarousel = asyncComponent(() => import("../embeddable/postscarousel/"));
const PageGallery = asyncComponent(() => import("../embeddable/pagegallery/"));
const PageModules = asyncComponent(() => import("../embeddable/pagemodules/"));

const FeaturedTabs = asyncComponent(() => import("../embeddable/featuredtabs/"));
const InlineList = asyncComponent(() => import("../embeddable/inlinelist/"));

const messages = {
    'en': messages_en
};

const components = {
    pageGallery: PageGallery,
    postsCarousel: PostsCarousel,
    chart: Chart,
    map:Map,
    filter: Filter,
    tabbedPosts: TabbedPosts,
    pageModules: PageModules,
    featuredTabs: FeaturedTabs,
    inlineList: InlineList
}

const store = getStore();

class EmbeddedGateway extends React.Component {

    constructor() {
        super();
        this.renderEmbeddedComponents = this.renderEmbeddedComponents.bind(this)
    }


    renderEmbeddedComponents() {
        const {intl: {locale}} = this.props

        const node = ReactDOM.findDOMNode(this)

        const elements = node.getElementsByClassName("tcdi-component")
        if (elements != null) {


            Array.from(elements).forEach((element,index) => {

                const component = element.getAttribute('data-component')
                element.removeAttribute("data-component")

                if (component) {
                    const props = {...this.props}
                    const attrs = element.attributes
                    for (var i = attrs.length - 1; i >= 0; i--) {
                        props[attrs[i].name] = attrs[i].value;
                    }
                    const C = components[component];
                    ReactDOM.render(
                        <Provider store={store}>
                            <IntlProvider locale={locale} messages={messages[locale]}>
                                <C unique={"embeddable_"+index} {...props} childContent={element.innerHTML}/>
                            </IntlProvider>
                        </Provider>, element);


                }
            })
        }
    }


    componentDidMount() {
        this.renderEmbeddedComponents()
    }

    componentDidUpdate(prevProps, prevState, snapshot) {
        const {parent} = this.props
        if (parent != prevProps.parent) {
            this.renderEmbeddedComponents()
        }
    }


    render() {
        const {parent, intl: {locale}} = this.props
        return <React.Fragment>
            {this.props.children}
        </React.Fragment>
    }
};

export default injectIntl(EmbeddedGateway)
