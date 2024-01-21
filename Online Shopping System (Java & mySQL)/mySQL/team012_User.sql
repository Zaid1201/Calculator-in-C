CREATE DATABASE  IF NOT EXISTS `team012` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `team012`;
-- MySQL dump 10.13  Distrib 8.0.34, for Win64 (x86_64)
--
-- Host: stusql.dcs.shef.ac.uk    Database: team012
-- ------------------------------------------------------
-- Server version	8.0.32

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `User`
--

DROP TABLE IF EXISTS `User`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `User` (
  `userID` char(36) NOT NULL,
  `userType` int NOT NULL DEFAULT '1',
  `forename` varchar(20) NOT NULL,
  `surname` varchar(20) NOT NULL,
  `email` varchar(30) NOT NULL,
  `password_hash` binary(48) NOT NULL,
  `bankCardNumber` binary(32) DEFAULT NULL,
  `bankCardName` binary(16) DEFAULT NULL,
  `expiryDate` binary(16) DEFAULT NULL,
  `securityCode` binary(16) DEFAULT NULL,
  `houseNumber` varchar(4) DEFAULT NULL,
  `postCode` varchar(8) DEFAULT NULL,
  PRIMARY KEY (`userID`),
  UNIQUE KEY `email_UNIQUE` (`email`),
  KEY `houseNumber` (`houseNumber`),
  KEY `postCode_idx` (`postCode`),
  KEY `address_idx` (`houseNumber`,`postCode`),
  CONSTRAINT `address` FOREIGN KEY (`houseNumber`, `postCode`) REFERENCES `Address` (`houseNumber`, `postCode`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `User`
--

LOCK TABLES `User` WRITE;
/*!40000 ALTER TABLE `User` DISABLE KEYS */;
INSERT INTO `User` VALUES ('c923fea8-ecfa-49f1-b692-49154e79f43a',3,'A','A','ypan@shef.ac.uk',_binary '0à\Z\ÏPZõ\Á°∏wıä≤¸D\„0\Î\œTˆ0íû{)vX8L§/¡5¯√øÒ,kI~¡N\›',_binary 'Ù/\Î\Ë±Y\Ï\⁄Õçu\ﬁ\ÍW\—/Äˆ3Ù\‘n:ºê^Æ\Í',_binary 'e≠\‡-\Âƒõe_êmÚS=˙',_binary ';\—ˆ÷¶\‡®\Ów \\w@î©',_binary 'ò∂9Vü˜ÅÚ˜i!m\∆Z','a','S1 4TT');
/*!40000 ALTER TABLE `User` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-12-01 14:37:49
