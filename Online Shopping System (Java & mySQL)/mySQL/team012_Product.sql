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
-- Table structure for table `Product`
--

DROP TABLE IF EXISTS `Product`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Product` (
  `code` varchar(6) NOT NULL,
  `brand` varchar(20) NOT NULL,
  `name` varchar(30) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `gauge` enum('OO','TT','N') NOT NULL,
  `quantity` int NOT NULL,
  PRIMARY KEY (`code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Product`
--

LOCK TABLES `Product` WRITE;
/*!40000 ALTER TABLE `Product` DISABLE KEYS */;
INSERT INTO `Product` VALUES ('C320','Peco',' Standard Controller',42.00,'OO',1),('C760','Dapol',' DCC Controller',46.00,'TT',35),('C890','Peco',' DCC Elite Controller',64.00,'TT',26),('L2310','Graham Farish',' Class A3 “Flying Scotsman”',43.00,'OO',75),('L2320','Bachmann',' Class A4 “Mallard”',36.00,'OO',86),('L2330','Graham Farish',' Class  5MT Black Five',26.00,'OO',71),('L2340','Peco',' Class 07 Austerity',48.00,'OO',58),('L2350','Dapol',' Class 7P Castle',46.00,'OO',73),('L2360','Hornby',' Class 7P Britannia',53.00,'OO',49),('L2380','Graham Farish',' Class 8P  Merchant Navy',65.00,'OO',85),('L2390','Peco',' Class 8F Stanier',28.00,'N',35),('L270','Bachmann','Class 8P Coronation',31.00,'OO',12),('M710','Bachmann',' Eurostar Train Set',85.00,'N',8),('M760','Hornby',' Flying Scotsman Train Set',94.00,'OO',3),('M780','Dapol',' Mixed Freight DCC Train Set',65.00,'OO',8),('P240','Peco',' 3rd Radius Starter Oval',39.00,'OO',10),('P270','Hornby',' Track Pack B',50.00,'OO',13),('P290','Dapol',' 2nd Radius Starter Oval',43.00,'OO',20),('P620','Dapol',' Track  Pack A',46.00,'OO',10),('R250','Bachmann','  Right-Hand Point Track',22.00,'TT',2),('R260','Bachmann',' Left Hand Point Track',3.00,'TT',35),('R5200','Hornby',' Single Straight',8.00,'TT',75),('R5300','Hornby',' Double Straight',12.00,'TT',66),('R6100','Graham Farish',' 10cm Single Curve Track',8.00,'N',67),('R615','Dapol',' 15cm Single Curve Track',10.00,'TT',53),('R6200','Dapol',' 20cm Single Curved Track',12.00,'TT',85),('R630','Hornby',' Left-Hand Crossover',6.00,'TT',80),('R640','Hornby',' Right-Hand Crossover',6.00,'TT',60),('R810','Graham Farish',' 10cm Double Curve Track',9.00,'TT',62),('R8150','Graham Farish',' 15cm Double Curve Track',13.00,'TT',42),('R8200','Graham Farish',' 20cm Double Curve Track',16.00,'TT',26),('S140','Peco',' 20t Hopper Wagon',24.00,'OO',40),('S150','Peco',' Cattle Wagon',26.00,'TT',52),('S170','Peco',' Horse Box Wagon',16.00,'OO',45),('S190','Peco',' 6-Plank Coal Wagon',23.00,'N',65),('S240','Peco',' Sleeper Car',35.00,'TT',52),('S250','Bachmann',' Restaurant Car',31.00,'TT',20),('S260','Bachmann',' Buffet Car',32.00,'OO',75);
/*!40000 ALTER TABLE `Product` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-12-01 14:37:46
