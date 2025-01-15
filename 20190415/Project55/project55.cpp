#include <stdio.h>
#include "mysql.h"
#pragma warning (disable:4996)

#pragma comment(lib, "libmysql.lib")

#define MAX_LEN 10000

const char* host = "localhost";
const char* user = "root";
const char* pw = "9877";
const char* db = "dbfirst";



void type1(MYSQL* connection);
void type2(MYSQL* connection);
void type3(MYSQL* connection);
void type4(MYSQL* connection);
void type5(MYSQL* connection);
void type6(MYSQL* connection);
void type7(MYSQL* connection);

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	int TYPE = -1;

	FILE* fp;
	int state = 0;
	char in[MAX_LEN];
	int state1 = 0;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{

		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		fp = fopen("20190415ci.txt", "r");
		if (!fp)
		{
			printf("FILE OPEN ERROR!\n");
			return -1;
		}
		while (!feof(fp)) {
			fgets(in, MAX_LEN, fp);
			state = mysql_query(connection, in);
		}
		fclose(fp);

		while (TYPE) {

		
			printf("\n\n\n\n");
			printf("------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n");
			printf("----------------------------------\n");
			scanf("%d", &TYPE);

			switch (TYPE) {
			case 1:
				type1(connection);
				break;
			case 2:
				type2(connection);
				break;
			case 3:
				printf("QUERY TYPES: 3\n");
				type3(connection);
				break;
			case 4:
				printf("QUERY TYPES: 4\n");
				type4(connection);
				break;
			case 5:
				printf("QUERY TYPES: 5\n");
				type5(connection);
				break;
			case 6:
				printf("QUERY TYPES: 6\n");
				type6(connection);
				break;
			case 7:
				printf("QUERY TYPES: 7\n");
				type7(connection);
				break;
			case 0:
				printf("----------------------------------\n");
				printf("\n\tQUIT THE PROGRAM\n\n");
				printf("----------------------------------\n");
			    fp = fopen("20190415_D.txt", "r");
				if (!fp)
				{
					printf("FILE OPEN ERROR!\n");
					return -1;
				}
				while (!feof(fp)) {
					fgets(in, MAX_LEN, fp);
					state1 = mysql_query(connection, in);
				}
				fclose(fp);
				return 0;
				break;
			default:
				printf("WRONG QUERY TYPES!!\n");
				break;
			}
		}



	}


		

	return 0;
}

void type1(MYSQL* connection) {
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int SUBTYPE = -1;
	int QUIT = -1;

	char tracknum[20];


	while (QUIT) {
		SUBTYPE = -1;
		printf("\n\n");
		printf("------------ TYPE 1 ------------\n\n");
		printf("** Assume the package shipped by USPS with tracking number X is reported to have been destroyed in an accident.Find the contact information for the custome.**\n");
		printf(" Which X? : ");
		scanf("%s", &tracknum);
		printf("\n\n--------------------------------\n");
		printf("shipper : USPS   tracking num : %s ", tracknum);

		
		printf("\n\n--------------------------------\n");
		char query[10000] = "\0";
		/*SELECT PHONE FROM CUSTOMER WHERE CUSTOMER_ID = (SELECT CUSTOMER_ID FROM SHIP_TO_SEND  WHERE shipper_name = 'USPS' AND TRACKINGNUM = 'T0001');*/
		sprintf(query, "SELECT CUSTOMER_ID,PHONE FROM CUSTOMER WHERE CUSTOMER_ID = (SELECT CUSTOMER_ID FROM SHIP_TO_SEND  WHERE shipper_name = '%s' AND TRACKINGNUM = '%s');", "USPS", tracknum);
		int state = 0;
		

		state = mysql_query(connection, query);
		if (state == 0)
		{
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf(" CUSTOMER_ID  : %s   PHONE NUMBER :  %s\n", sql_row[0],sql_row[1]);
			}
			mysql_free_result(sql_result);
		}


		while (SUBTYPE) {
			printf("\n\n\n\n");
			printf("------------ Subtypes in TYPE 1 ------------\n\n");
			printf("\t1. TYPE 1-1\n");
			printf("\t2. RESTART TYPE 1\n");
			printf("\t0. QUIT TO SELECT QUERY TYPES\n");
			printf("--------------------------------------------\n");
			scanf("%d", &SUBTYPE);
			QUIT = SUBTYPE;
			if (SUBTYPE == 1)
			{
				printf("\n\n");
				printf("------------ TYPE 1-1 ------------\n\n");
				printf("**Then find the contents of that shipment and create a new shipment of replacement items. **\n");
				
				char query2[10000] = "\0";
				sprintf(query2, "SELECT PTYPE FROM PRODUCT WHERE PRODUCT_ID = \
                (SELECT PRODUCT_ID FROM BUY WHERE CUSTOMER_ID = (SELECT CUSTOMER_ID FROM SHIP_TO_SEND  WHERE shipper_name = '%s' AND TRACKINGNUM = '%s'));", "USPS", tracknum);
				int state2 = 0;


				state2 = mysql_query(connection, query2);
				if (state2 == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("PRODUCT TYPE : %-14s \n", sql_row[0]);
					}

					mysql_free_result(sql_result);
				}
				
				char query3[10000] = "\0";
				sprintf(query3, " SET @VAR1 = (SELECT CUSTOMER_ID FROM SHIP_TO_SEND  WHERE shipper_name = '%s' AND TRACKINGNUM = '%s');\
				DELETE FROM SHIP_TO_SEND WHERE CUSTOMER_ID = @VAR1 AND SHIPPER_NAME = '%s';\
				INSERT INTO SHIP_TO_SEND VALUES(@VAR1, '%s', '%s'); ","USPS", tracknum,"USPS","USPS",tracknum);
				int state3 = 0;


				state3 = mysql_query(connection, query3);
				if (state3 == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
					}
					mysql_free_result(sql_result);
				}
			}
			else if (SUBTYPE == 2)
			{
				SUBTYPE = 0;
			}
		}
	}
		
	return;
}


void type2(MYSQL* connection) {
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int SUBTYPE = -1;
	int QUIT = -1;
	while (QUIT) {
		SUBTYPE = -1;
		printf("\n\n");
		printf("------------ TYPE 2 ------------\n\n");
		printf("**  Find the customer who has bought the most (by price) in the past year **\n");
		/*select customer_id from buy where product_id = (select product_id from product where price = (select price from buy as b,product as p where p.product_id = b.product_id and buy_date >='2021-01-01' and buy_date<'2022-12-09)' order by cast(price as unsigned) desc limit 1));*/
		char query[10000] = "\0";
		sprintf(query, "SELECT CUSTOMER_ID FROM BUY WHERE PRODUCT_ID = \
			(SELECT\
				product_id\
				FROM\
				product\
				WHERE\
				price = (SELECT\
					price\
					FROM\
					buy AS b,\
					product AS p\
					WHERE\
					p.product_id = b.product_id\
					AND buy_date >= '2021-01-01'\
					AND buy_date < '2022-12-09)'\
					ORDER BY CAST(price AS UNSIGNED) DESC\
					LIMIT 1))");
		int state = 0;

		state = mysql_query(connection, query);
		if (state == 0)
		{
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("CUSTOMER_ID : %-14s \n", sql_row[0]);
			}
			mysql_free_result(sql_result);
		}
		else
			printf("%s", mysql_error(connection));

		while (SUBTYPE) {
			printf("\n\n\n\n");
			printf("------------ Subtypes in TYPE2 ------------\n\n");
			printf("\t1. TYPE 2-1\n");
			printf("\t2. RESTART TYPE 2\n");
			printf("\t0. QUIT TO SELECT QUERY TYPES\n");
			printf("--------------------------------------------\n");
			scanf("%d", &SUBTYPE);
			QUIT = SUBTYPE;
			//TYPE 2-1
			if (SUBTYPE == 1)
			{
				printf("\n\n");
				printf("------------ TYPE 2-1 ------------\n\n");
				printf("** ) Then find the product that the customer bought the most. (**\n");


				char query2[10000] = "\0";
				sprintf(query2, "select product_id from product where price = (select price from\
					buy as b, product as p where p.product_id = b.product_id and buy_date\
					>= '2021-01-01' and buy_date < '2022-12-09)' order by cast(price as unsigned) desc limit 1);");

				int state1 = 0;


				state1 = mysql_query(connection, query2);
				if (state1 == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("PRODUCT_ID :  %-14s", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
			}
			else if (SUBTYPE == 2)
			{
				SUBTYPE = 0;
			}
		}
	}
	return;
}
void type3(MYSQL* connection) {
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int SUBTYPE = -1;
	int QUIT = -1;
	while (QUIT) {
		SUBTYPE = -1;
		printf("\n\n");
		printf("------------ TYPE 3 ------------\n\n");
		printf("**  Find ALL products sold In the past year **\n");
		/*select customer_id from buy where product_id = (select product_id from product where price = (select price from buy as b,product as p where p.product_id = b.product_id and buy_date >='2021-01-01' and buy_date<'2022-12-09)' order by cast(price as unsigned) desc limit 1));*/
		char query[10000] = "\0";
		sprintf(query, "select DISTINCT prODUCT_ID froM	 buy where\
			  buy_date >='2021-01-01' and buy_date<'2022-12-09';\
		");
		int state = 0;

		state = mysql_query(connection, query);
		if (state == 0)
		{
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("product_id : %-14s \n", sql_row[0]);
			}
			mysql_free_result(sql_result);
		}

		while (SUBTYPE) {
			printf("\n\n\n\n");
			printf("------------ Subtypes in TYPE3 ------------\n\n");
			printf("\t1. TYPE 3-1\n");
			printf("\t2. TYPE 3-2\n");

			printf("\t3. RESTART TYPE 3\n");
			printf("\t0. QUIT TO SELECT QUERY TYPES\n");
			printf("--------------------------------------------\n");
			fflush(stdin);
			scanf("%d", &SUBTYPE);
			fflush(stdin);
			QUIT = SUBTYPE;
			//TYPE 2-1
			if (SUBTYPE == 1)
			{
				printf("\n\n");
				printf("------------ TYPE 3-1 ------------\n\n");
				printf("** ) Then find the top k products by dollar-amount sold. **\n");
				

				char query8[10000] = "\0";
				int k;
				printf("WHAT IS K?");
				scanf("%d", &k);

				sprintf(query8, "SELECT PRODUCT_ID , SUM(PRICE) FROM\
					(SELECT B.PRODUCT_ID, PRICE FROM PRODUCT AS P\
					,BUY AS B WHERE BUY_DATE>= '2021-01-01' and\
					 buy_date < '2022-12-09'AND  B.PRODUCT_ID = P.PRODUCT_ID )H\
					 GROUP BY PRODUCT_ID ORDER BY SUM(PRICE) DESC LIMIT %d", k);
				int state = 0;


				state = mysql_query(connection, query8);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("product_id, sum(price) : %s    %s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
			}
			if (SUBTYPE == 2)
			{
				printf("\n\n");
				printf("------------ TYPE 3-2 ------------\n\n");
				printf("** ) Then find the top 10 PERCENT  products by dollar-amount sold. **\n");
				printf("\n\n--------------------------------\n");
				printf("--------------------------------\n");
				char query9[10000] = "\0";

				sprintf(query9,"set @var4 =  (SELECT   SUM(PRICE) FROM\
					(SELECT B.PRODUCT_ID, PRICE FROM PRODUCT AS P\
						, BUY AS B WHERE BUY_DATE >= '2021-01-01' and\
						buy_date < '2022-12-09'AND  B.PRODUCT_ID = P.PRODUCT_ID)H\
					GROUP BY product_id with rollup order by sum(price) desc limit 1);\
				select product_id from product where price <= (@var4 / 10); ");
				int state = 0;

				state = mysql_query(connection, query9);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("product_id : %-9s\n", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				
			}
			if (SUBTYPE == 3)
			{
				SUBTYPE = 0;
			}
		}
	}
	return;
}
void type4(MYSQL* connection) {
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int SUBTYPE = -1;
	int QUIT = -1;

	while (QUIT) {
		QUIT = -1;
		printf("\n\n");
		printf("------------ TYPE 4 ------------\n\n");
		printf("**  Find all products by unit sales in the past year**\n");
		

		
		printf("\n\n--------------------------------\n");
		printf("--------------------------------\n");
		char query[10000] = "\0";
		sprintf(query, "SELECT PRODUCT_ID , COUNT(PRODUCT_ID) FROM (select prODUCT_ID from buy where\
			buy_date >= '2021-01-01' and buy_date < '2022-12-09')K GROUP BY PRODUCT_ID HAVING\
			 COUNT(PRODUCT_ID) > 0 " );
		int state = 0;


		state = mysql_query(connection, query);
		if (state == 0)
		{
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("PRODUCT_ID AND  COUNT : %s    %s\n", sql_row[0], sql_row[1]);
			}
			mysql_free_result(sql_result);
		}
		while (SUBTYPE) {
			SUBTYPE = -1;
			printf("\n\n\n\n");
			printf("------------ Subtypes in TYPE4 ------------\n\n");
			printf("\t1. TYPE 4-1\n");
			printf("\t2. TYPE 4-2\n");
			printf("\t3. RESTART TYPE 3\n");
			printf("\t0. QUIT TO SELECT QUERY TYPES\n");
			printf("--------------------------------------------\n");
			scanf("%d", &SUBTYPE);
			QUIT = SUBTYPE;
			//TYPE 3-1
			if (SUBTYPE == 1)
			{
				printf("\n\n");
				printf("------------ TYPE 4-1 ------------\n\n");
				printf("**  Then find the top k products by unit sales.. **\n");
				printf("\n\n--------------------------------\n");
				int k;
				printf("WHAT IS K?");
				scanf("%d", &k);
				printf("--------------------------------\n");
				char query1[10000] = "\0";
				sprintf(query1, "SELECT PRODUCT_ID , COUNT(PRODUCT_ID) FROM (select prODUCT_ID froM	 buy where\
					buy_date >= '2021-01-01' and buy_date < '2022-12-09')K GROUP BY PRODUCT_ID HAVING\
					COUNT(PRODUCT_ID) > 0 ORDER BY COUNT(PRODUCT_ID) DESC LIMIT %d ; ",k);
				int state1 = 0;

				state1 = mysql_query(connection, query1);
				if (state1 == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("product_id and count  %s %s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
			}
			else if (SUBTYPE == 2) {
				printf("\n\n");
				printf("------------ TYPE 4-2 ------------\n\n");
				printf("**   And then find the top 10percent  products by unit sales.\n");
				printf("\n\n--------------------------------\n");
				printf("--------------------------------\n");
				char query2[10000] = "\0";
				sprintf(query2, "set @var5 = (SELECT COUNT(PRODUCT_ID) FROM (select prODUCT_ID froM	 buy where\
					buy_date >= '2021-01-01' and buy_date < '2022-12-31')K GROUP BY PRODUCT_ID with rollup HAVING COUNT(PRODUCT_ID) > 0 ORDER BY COUNT(PRODUCT_ID)  DESC LIMIT 1);\
					SELECT product_id, COUNT(PRODUCT_ID) FROM(select prODUCT_ID froM	 buy where\
						buy_date >= '2021-01-01' and buy_date < '2022-12-31')K  GROUP BY PRODUCT_ID  HAVING COUNT(PRODUCT_ID) <= (@var5 / 10)");
				int state1 = 0;

				state1 = mysql_query(connection, query2);
				if (state1 == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("product_id   and   count :  %s   %s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
				else
					printf("%s", mysql_error(connection));

			}
			else if (SUBTYPE == 3)
			{
				SUBTYPE = 0;
			}
		}
	}
	return;
}


void type5(MYSQL* connection) {
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int SUBTYPE = -1;
	int QUIT = -1;



	while (QUIT) {
		SUBTYPE = -1;
		printf("\n\n");
		printf("------------ TYPE 5 ------------\n\n");
		printf("**  Find those products that are out-of-stock at every store in California..**\n");

		printf("\n\n--------------------------------\n");


		printf("\n\n--------------------------------\n");
		char queryr[10000] = "\0";
		sprintf(queryr, "SELECT PRODUCT_ID FROM OFF_SALE AS A,STORE AS B WHERE A.STORE_ID = B.STORE_ID AND STORE_REGION = 'CALI' AND QUANTITY_PRODUCT_STORE = '0';");
		int state = 0;


		state = mysql_query(connection, queryr);
		if (state == 0)
		{
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf(" SOLD OUT IN CALI STORE : PRODUCT_ID  : %s   \n", sql_row[0]);
			}
			mysql_free_result(sql_result);
		}
		else
			printf("%s",mysql_error(connection));

		while (SUBTYPE) {
			printf("\n\n\n\n");
			printf("------------ ------------\n\n");
			printf("\t1. RESTART TYPE 1\n");
			printf("\t0. QUIT TO SELECT QUERY TYPES\n");
			printf("--------------------------------------------\n");
			scanf("%d", &SUBTYPE);
			QUIT = SUBTYPE;
			
			if (SUBTYPE == 1)
			{
				SUBTYPE = 0;
			}
		}
	}

	return;

}
void type6(MYSQL* connection) {
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int SUBTYPE = -1;
	int QUIT = -1;



	while (QUIT) {
		SUBTYPE = -1;
		printf("\n\n");
		printf("------------ TYPE 6 ------------\n\n");
		printf("**  Find those packages that were not delivered within the promised time.**\n");

		printf("\n\n--------------------------------\n");


		printf("\n\n--------------------------------\n");
		char queryr[10000] = "\0";
		sprintf(queryr, "select DISTINCT T.product_id from buy as b, track as t where b.product_id =t.product_id and buy_date!=predict_date");
		int state = 0;


		state = mysql_query(connection, queryr);
		mysql_error(connection);
		if (state == 0)
		{
			sql_result = mysql_store_result(connection) ;
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("  %s   \n", sql_row[0]);
			}
			mysql_free_result(sql_result);
		}
		else
			printf("%s", mysql_error(connection));


		while (SUBTYPE) {
			printf("\n\n\n\n");
			printf("------------ ------------\n\n");
			printf("\t1. RESTART TYPE 1\n");
			printf("\t0. QUIT TO SELECT QUERY TYPES\n");
			printf("--------------------------------------------\n");
			scanf("%d", &SUBTYPE);
			QUIT = SUBTYPE;

			if (SUBTYPE == 1)
			{
				SUBTYPE = 0;
			}
		}
	}

	return;


}
void type7(MYSQL* connection) {
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int SUBTYPE = -1;
	int QUIT = -1;



	while (QUIT) {
		SUBTYPE = -1;
		printf("\n\n");
		printf("------------ TYPE 7 ------------\n\n");
		printf("**Generate the bill for each customer for the past month.  .**\n");

		printf("\n\n--------------------------------\n");


		printf("\n\n--------------------------------\n");
		char queryr[10000] = "\0";
		sprintf(queryr, "SELECT B.CUSTOMER_ID, P.PRODUCT_ID, P.PRICE, BUY_DATE FROM BUY AS B,PRODUCT AS P WHERE B.PRODUCT_ID = P.PRODUCT_ID AND BUY_DATE >'2022-05-01'AND BUY_DATE <'2022-06-01'");
		int state = 0;
		

		state = mysql_query(connection, queryr);
		mysql_error(connection);
		if (state == 0)
		{
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("  %s   %s   %s   %s  \n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
			}
			mysql_free_result(sql_result);
		}
		else
			printf("%s", mysql_error(connection));


		while (SUBTYPE) {
			printf("\n\n\n\n");
			printf("------------ ------------\n\n");
			printf("\t1. RESTART TYPE 7\n");
			printf("\t0. QUIT TO SELECT QUERY TYPES\n");
			printf("--------------------------------------------\n");
			scanf("%d", &SUBTYPE);
			QUIT = SUBTYPE;

			if (SUBTYPE == 1)
			{
				SUBTYPE = 0;
			}
		}
	}

		return;

}




/*

	printf("------- SELECT QUERY TYPES -------\n\n");
	printf("\t1. TYPE 1\n");
	printf("\t2. TYPE 2\n");
	printf("\t3. TYPE 3\n");
	printf("\t4. TYPE 4\n");
	printf("\t5. TYPE 5\n");
	printf("\t6. TYPE 6\n");
	printf("\t7. TYPE 7\n");
	printf("\t0. QUIT\n");
	//printf("----------------------------------\n");
	printf("\n\n");
	printf("---- TYPE 5 ----\n\n");
	printf("** Find the top k brands by unit sales by the year**\n");
	printf(" Which K? : 3\n");

	return 0;

}(SELECT  product_id, SUM(PRICE) FROM
					(SELECT B.PRODUCT_ID, PRICE FROM PRODUCT AS P
					,BUY AS B WHERE BUY_DATE>= '2021-01-01' and
					 buy_date < '2022-12-09'AND  B.PRODUCT_ID = P.PRODUCT_ID )H
					 GROUP BY product_id with rollup order by sum(price) desc limit 1);
*/