-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema bankdb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema bankdb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `bankdb` DEFAULT CHARACTER SET utf8 ;
USE `bankdb` ;

-- -----------------------------------------------------
-- Table `bankdb`.`account`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bankdb`.`account` (
  `idaccount` INT NOT NULL,
  `creditSaldo` DECIMAL(10,2) NULL,
  `creditMax` DECIMAL(10,2) NULL,
  `accNumDebit` INT NULL,
  `accNumCredit` INT NULL,
  PRIMARY KEY (`idaccount`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bankdb`.`customer`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bankdb`.`customer` (
  `idcustomer` INT NOT NULL,
  `first_name` VARCHAR(45) NULL,
  `last_name` VARCHAR(45) NULL,
  `age` CHAR(3) NULL,
  `id_accounts` INT NULL,
  PRIMARY KEY (`idcustomer`),
  UNIQUE INDEX `idcustomer_UNIQUE` (`idcustomer` ASC) VISIBLE,
  INDEX `id_accounts_idx` (`id_accounts` ASC) VISIBLE,
  CONSTRAINT `id_accounts`
    FOREIGN KEY (`id_accounts`)
    REFERENCES `bankdb`.`account` (`idaccount`)
    ON DELETE CASCADE
    ON UPDATE RESTRICT)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bankdb`.`card`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bankdb`.`card` (
  `idcard` VARCHAR(20) NOT NULL,
  `fourdigitpin` VARCHAR(255) NULL,
  `id_omistaja` INT NULL,
  `id_account` INT NULL,
  PRIMARY KEY (`idcard`),
  UNIQUE INDEX `id_omistaja_UNIQUE` (`id_omistaja` ASC) VISIBLE,
  INDEX `id_account_idx` (`id_account` ASC) VISIBLE,
  CONSTRAINT `id_omistaja`
    FOREIGN KEY (`id_omistaja`)
    REFERENCES `bankdb`.`customer` (`idcustomer`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  CONSTRAINT `id_account`
    FOREIGN KEY (`id_account`)
    REFERENCES `bankdb`.`account` (`idaccount`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bankdb`.`transactions`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bankdb`.`transactions` (
  `idtransactions` INT NOT NULL,
  `date_transactions` DATE NULL,
  `amount` DECIMAL(10,2) NULL,
  `transactionscol` VARCHAR(45) NULL,
  `id_accountRef` INT NULL,
  PRIMARY KEY (`idtransactions`),
  INDEX `id_accountRef_idx` (`id_accountRef` ASC) VISIBLE,
  CONSTRAINT `id_accountRef`
    FOREIGN KEY (`id_accountRef`)
    REFERENCES `bankdb`.`account` (`idaccount`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
