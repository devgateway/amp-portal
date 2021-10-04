import { Button, Container, Menu } from "semantic-ui-react";
import React, { useEffect, useState } from "react";
import { MenuConsumer, MenuProvider, utils } from "@devgateway/wp-react-lib";
import { injectIntl } from "react-intl";
import { useHistory, withRouter } from "react-router";


const getPath = (menu, match) => {
  let path = [];
  menu.items.forEach(item => {
    if (item.child_items) {
      item.child_items.forEach(ch => {
        if (ch.slug === match.params.slug) {
          path.push(item)
          path.push(ch)
        }
      })
    } else if (item.slug === match.params.slug && item.url !== '/') {
      path.push(item)
    }


  })
  return path
}


const BreadCrumbs = withRouter(injectIntl(({ menu, match, intl }) => {

  let path = getPath(menu, match)
  return <React.Fragment>
    <a href={"#"}> Home </a>
    {path.map(i => !i.child_items ? <a className={i.slug === match.params.slug ? 'active' : ''}
                                       href={utils.replaceLink(i.url, intl.locale)}> {i.post_title}</a> :
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
                                             intl: { locale }
                                           }) => {

  useEffect(() => {
    if (!selected) {
      const pathSelected = getPath(menu, match)
      const items = pathSelected.filter(i => i.menu_item_parent === 0)
      if (items) {
        onSetSelected(items[0])
      }
    }

  }, [menu])


  return menu && <React.Fragment>

    {menu.items.map(i => {
      return (
        <Menu.Item
          key={i.ID}
          className={`divided ${i.child_items ? 'has-child-items' : ''} 
                   ${selected && selected.ID === i.ID ? 'selected' : ''}  ${active === i.slug ? "active" : ""}`}
        >

          {withIcons && <div className={"mark"} />} {i.child_items ?
          <span onMouseOver={() => onSetSelected(i)}>{i.title}</span> :
          <a onMouseOver={() => onSetSelected(i)} href={utils.replaceLink(i.url, locale)}
             target={i.type_label === 'Custom Link' ? "_blank" : "_self"}>{i.title}</a>}

        </Menu.Item>);
    })}

  </React.Fragment>
}))
const Header = ({ intl, match }) => {
  const history = useHistory();

  const goToEng = (e) => {
    console.log('go to eng clicked');
    console.log(e);
    handleClick('en', e);
  }
  const goToFrench = (e) => {
    console.log('go to french clicked');
    console.log(e);
    handleClick('fr', e);
  }
  const handleClick = (l, e) => {
    const slugUrl = slug ? `/${slug}` : ``;
    if (l === intl.locale) {
      e.preventDefault();
    } else {
      history.push(`/${l}${slugUrl}`);
    }
  }
  const [selected, setSelected] = useState()
  const { slug } = match.params;
  const logoUrl = process.env.REACT_APP_USE_HASH_LINKS ? `/#/${intl.locale}` : `/${intl.locale}`;
  const showSubPages = false;
  return <React.Fragment>


    <MenuProvider slug={"main"}>
      <Container fluid={true} className="header">
        <Container fluid={true} className={"background"}>
          <Menu className={"branding"} text>
            <Menu.Item>
              <a href={logoUrl}>
                <img className="logo" loading="lazy"
                     src={`${process.env.REACT_APP_AMP_URL}/aim/default/displayFlag.do`} alt="" />
                <span className="label">{intl.formatMessage({
                  id: 'app.title-small',
                  defaultMessage: "AMP Portal"
                })}</span></a>

            </Menu.Item>
            <Menu.Menu className={"pages"}>
              <MenuConsumer>
                <MyMenuItems active={slug} selected={selected}
                             onSetSelected={setSelected} />
              </MenuConsumer>
            </Menu.Menu>
            <span className="lang">
                          <Button
                            attached='left' className={intl.locale === 'en' ? 'selected' : ''}
                            onClick={goToEng}
                          >EN</Button>
                          <Button attached='left' className={intl.locale === 'fr' ? 'selected' : ''}
                                  onClick={goToFrench}
                          >FR</Button>
                        </span>
            <Menu.Item fitted className="login">
              <img src='/login.svg' alt="" /> {intl.locale === 'en' ? 'Login to AMP' : 'Se Connecter'}
            </Menu.Item>
          </Menu>

        </Container>

        {showSubPages && (<Container fluid={true} className={"child"}>
          {selected && selected.child_items && <Menu fluid text>
            <MyMenuItems active={slug} withIcons onSetSelected={() => null}
                         menu={{ items: selected.child_items }}>}</MyMenuItems>

          </Menu>}
        </Container>)}
      </Container>


      {showSubPages && (<Container className={"url breadcrumbs"}>
          <MenuConsumer>
            <BreadCrumbs />
          </MenuConsumer>
        </Container>
      )}
    </MenuProvider>
  </React.Fragment>

}


export default injectIntl(withRouter(injectIntl(Header)))