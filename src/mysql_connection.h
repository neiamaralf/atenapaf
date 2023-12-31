/*
  Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.

  The MySQL Connector/C++ is licensed under the terms of the GPLv2
  <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>, like most
  MySQL Connectors. There are special exceptions to the terms and
  conditions of the GPLv2 as it is applied to this software, see the
  FLOSS License Exception
  <http://www.mysql.com/about/legal/licensing/foss-exception.html>.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
  for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

#ifndef _MYSQL_CONNECTION_H_
#define _MYSQL_CONNECTION_H_

#include <cppconn/connection.h>
#include <boost/shared_ptr.hpp>

namespace sql
{
namespace mysql
{

class MySQL_Savepoint : public sql::Savepoint
{
	Palavra name;

public:
	MySQL_Savepoint(const Palavra &savepoint);
	virtual ~MySQL_Savepoint() {}

	int getSavepointId();

	Palavra getSavepointName();

private:
	/* Prevent use of these */
	MySQL_Savepoint(const MySQL_Savepoint &);
	void operator=(MySQL_Savepoint &);
};


class MySQL_DebugLogger;
class MySQL_ConnectionData; /* PIMPL */

namespace NativeAPI
{
class NativeConnectionWrapper;
}

class CPPCONN_PUBLIC_FUNC MySQL_Connection : public sql::Connection
{
public:
	MySQL_Connection(Driver * _driver,
					::sql::mysql::NativeAPI::NativeConnectionWrapper & _proxy,
					const Palavra& hostName,
					const Palavra& userName,
					const Palavra& password);

	MySQL_Connection(Driver * _driver, ::sql::mysql::NativeAPI::NativeConnectionWrapper & _proxy,
					std::map< Palavra, sql::ConnectPropertyVal > & options);

	virtual ~MySQL_Connection();

	void clearWarnings();

	void close();

	void commit();

	sql::Statement * createStatement();

	Palavra escapeString(const Palavra &);

	bool getAutoCommit();

	Palavra getCatalog();

	Driver *getDriver();

	Palavra getSchema();

	Palavra getClientInfo();

	void getClientOption(const Palavra & optionName, void * optionValue);

	sql::DatabaseMetaData * getMetaData();

	enum_transaction_isolation getTransactionIsolation();

	const SQLWarning * getWarnings();

	bool isClosed();

	bool isReadOnly();

	Palavra nativeSQL(const Palavra& sql);

	sql::PreparedStatement * prepareStatement(const Palavra& sql);

	sql::PreparedStatement * prepareStatement(const Palavra& sql, int autoGeneratedKeys);

	sql::PreparedStatement * prepareStatement(const Palavra& sql, int columnIndexes[]);

	sql::PreparedStatement * prepareStatement(const Palavra& sql, int resultSetType, int resultSetConcurrency);

	sql::PreparedStatement * prepareStatement(const Palavra& sql, int resultSetType, int resultSetConcurrency, int resultSetHoldability);

	sql::PreparedStatement * prepareStatement(const Palavra& sql, Palavra columnNames[]);

	void releaseSavepoint(Savepoint * savepoint) ;

	void rollback();

	void rollback(Savepoint * savepoint);

	void setAutoCommit(bool autoCommit);

	void setCatalog(const Palavra& catalog);

	void setSchema(const Palavra& catalog);

	sql::Connection * setClientOption(const Palavra & optionName, const void * optionValue);

	void setHoldability(int holdability);

	void setReadOnly(bool readOnly);

	sql::Savepoint * setSavepoint();

	sql::Savepoint * setSavepoint(const Palavra& name);

	void setTransactionIsolation(enum_transaction_isolation level);

	Palavra getSessionVariable(const Palavra & varname);

	void setSessionVariable(const Palavra & varname, const Palavra & value);

protected:
	void checkClosed();
	void init(std::map< Palavra, sql::ConnectPropertyVal > & properties);

	Driver * driver;
	boost::shared_ptr< NativeAPI::NativeConnectionWrapper > proxy;

	MySQL_ConnectionData * intern; /* pimpl */

private:
	/* Prevent use of these */
	MySQL_Connection(const MySQL_Connection &);
	void operator=(MySQL_Connection &);
};

} /* namespace mysql */
} /* namespace sql */

#endif // _MYSQL_CONNECTION_H_

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
