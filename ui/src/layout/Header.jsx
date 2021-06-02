import {Container, Flag, Menu} from "semantic-ui-react";
import React, {useEffect, useState} from "react";
import MenuProvider from "../wp/providers/MenuProvider";
import MenuConsumer from "../wp/consumers/MenuConsumer";
import {injectIntl} from "react-intl";
import {replaceLink} from '../wp/htmlUtils'
import {withRouter} from "react-router";
import Search from '../wp/Search'

const getPath = (menu, match) => {
    let path = [];
    menu.items.forEach(item => {
        if (item.child_items) {
            item.child_items.forEach(ch => {
                if (ch.slug == match.params.slug) {
                    path.push(item)
                    path.push(ch)
                }
            })
        } else if (item.slug == match.params.slug && item.url != '/') {
            path.push(item)
        }


    })
    return path
}


const BreadCrumbs = withRouter(injectIntl(({menu, match, intl}) => {

    let path = getPath(menu, match)
    return <React.Fragment>
        <a href={"#"}> Home </a>
        {path.map(i => !i.child_items ? <a className={i.slug == match.params.slug ? 'active' : ''}
                                           href={replaceLink(i.url, intl.locale)}> {i.post_title}</a> :
            <span>{i.post_title} </span>)}
    </React.Fragment>

}))


const MyMenuItems = injectIntl(withRouter(({
                                               withIcons,
                                               active,
                                               menu,
                                               onSetSelected,
                                               selected,
                                               match,
                                               intl: {locale}
                                           }) => {

    useEffect((e) => {
        if (!selected) {
            const pathSelected = getPath(menu, match)
            const items = pathSelected.filter(i => i.menu_item_parent == 0)
            if (items) {
                onSetSelected(items[0])
            }
        }

    }, [menu])


    return menu && <React.Fragment>

        {menu.items.map(i => (
            <Menu.Item
                className={`divided ${i.child_items ? 'has-child-items' : ''} 
                 ${selected && selected.ID == i.ID ? 'selected' : ''}  ${active == i.slug ? "active" : ""}`}
                >

                {withIcons && <div  className={"mark"}></div>} {i.child_items ? <span onMouseOver={e => onSetSelected(i)}>{i.title}</span> :
                <a onMouseOver={e => onSetSelected(i)} href={replaceLink(i.url, locale)}>{i.title}</a>}

            </Menu.Item>))}

    </React.Fragment>
}))

const Header = ({intl, match}) => {

    const [selected, setSelected] = useState()
    const {slug} = match.params

    return <React.Fragment>


        <MenuProvider slug={"main"}>
            <Container fluid={true} className="header">
                <Container fluid={true} className={"background"}>

                    <Menu className={"branding"} text>
                        <Menu.Item>
                            <a href="/"><img className="brand logo" size="large" src='logo.png' width={"100px"}/></a>
                        </Menu.Item>

                        <Menu.Item className={"divider"}>
                            <div></div>
                        </Menu.Item>

                        <Menu.Item fitted>

                            <Flag name="ar"/>
                            WP React
                        </Menu.Item>

                        <Menu.Menu className={"pages"}>
                            <MenuConsumer>
                                <MyMenuItems active={slug} selected={selected}
                                             onSetSelected={setSelected}></MyMenuItems>
                            </MenuConsumer>
                        </Menu.Menu>

                        <Menu.Item fitted>

                        </Menu.Item>
                    </Menu>

                </Container>

                <Container fluid={true} className={"child"}>
                    {selected && selected.child_items && <Menu fluid text>
                        <MyMenuItems active={slug} locale={intl.locale} withIcons onSetSelected={e => null}
                                     menu={{items: selected.child_items}}>}</MyMenuItems>

                    </Menu>}
                </Container>
            </Container>


            <Container className={"url breadcrumbs"}>
                <MenuConsumer>
                    <BreadCrumbs></BreadCrumbs>
                </MenuConsumer>

            </Container>
        </MenuProvider>
    </React.Fragment>

}


export default injectIntl(withRouter(Header))