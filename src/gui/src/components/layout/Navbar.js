import React from "react";
import { AppBar, Toolbar, Button } from "@material-ui/core";
import { makeStyles } from "@material-ui/core/styles";
import GitHubIcon from "@material-ui/icons/GitHub";

const useStyles = makeStyles((theme) => ({
  margin: {
    margin: theme.spacing(1),
  },
  root: {
    flex: 1,
  },
}));

const Navbar = () => {
  const classes = useStyles();

  return (
    <AppBar position="absolute" className={classes.root}>
      <Toolbar variant="dense">
        <Button
          variant="contained"
          color="primary"
          fontSize="large"
          disableElevation
          className={classes.margin}
        >
          Home
        </Button>
        <Button
          variant="contained"
          color="primary"
          fontSize="large"
          disableElevation
          className={classes.margin}
        >
          About
        </Button>
        <Button
          variant="contained"
          color="primary"
          fontSize="large"
          disableElevation
          className={classes.margin}
        >
          Support
        </Button>
        <GitHubIcon fontSize="large" />
      </Toolbar>
    </AppBar>
  );
};

export default Navbar;
