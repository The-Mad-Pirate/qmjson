//
// QtMark JSON Library
//
// Copyright (C) 2015 Assured Information Security, Inc.
// Author: Rian Quinn       <quinnr@ainfosec.com>
// Author: Rodney Forbes    <forbesr@ainfosec.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

// ============================================================================
// Includes
// ============================================================================

#include <qmjsonarray.h>
#include <qmjsonobject.h>

// ============================================================================
// QMJsonArray Implementation
// ============================================================================

QMJsonArray::QMJsonArray()
{
}

QMJsonArray::QMJsonArray(const QList<QMPointer<QMJsonValue> > &list)
{
    mList = list;
}

QMJsonArray::~QMJsonArray()
{
}

void QMJsonArray::reserve(int32_t alloc)
{
    mList.reserve(alloc);
}

void QMJsonArray::clear(void)
{
    for(const auto &value : mList)
    {
        if(value->isObject() == true)
        {
            value->toObject()->clear();
            continue;
        }

        if(value->isArray() == true)
        {
            value->toArray()->clear();
            continue;
        }
    }

    while(mList.count() > 0)
        this->removeFirst();
}

int32_t QMJsonArray::count(void) const
{
    return mList.count();
}

bool QMJsonArray::isEmpty(void) const
{
    return mList.isEmpty();
}

bool QMJsonArray::contains(const QMPointer<QMJsonValue> &value) const
{
    return mList.contains(value);
}

int32_t QMJsonArray::indexOf(const QMPointer<QMJsonValue> &value) const
{
    return mList.indexOf(value);
}

int32_t QMJsonArray::lastIndexOf(const QMPointer<QMJsonValue> &value, int32_t from) const
{
    return mList.lastIndexOf(value, from);
}

bool QMJsonArray::endsWith(const QMPointer<QMJsonValue> &value) const
{
    return mList.endsWith(value);
}

bool QMJsonArray::startsWith(const QMPointer<QMJsonValue> &value) const
{
    return mList.startsWith(value);
}

void QMJsonArray::prepend(const QMPointer<QMJsonValue> &value)
{
    this->insert(0, value);
}

void QMJsonArray::append(const QMPointer<QMJsonValue> &value)
{
    this->insert(mList.count(), value);
}

void QMJsonArray::insert(int32_t index, const QMPointer<QMJsonValue> &value)
{
    if(index < 0) index = 0;
    if(index > mList.count()) index = mList.count();

    if(value.isNull() == true)
    {
        auto newValue = QMPointer<QMJsonValue>(new QMJsonValue);

        mList.insert(index, newValue);
        emit itemAdded(index, newValue);
    }
    else
    {
        mList.insert(index, value);
        emit itemAdded(index, value);
    }
}

void QMJsonArray::unite(const QMPointer<QMJsonArray> &array)
{
    if(array.isNull() == true)
        return;

    for(const auto &value : array->values())
        this->append(value);
}

void QMJsonArray::removeAll(const QMPointer<QMJsonValue> &value)
{
    while(mList.contains(value) == true)
        this->removeAt(mList.indexOf(value));
}

void QMJsonArray::removeOne(const QMPointer<QMJsonValue> &value)
{
    this->removeAt(mList.indexOf(value));
}

void QMJsonArray::removeAt(int32_t index)
{
    if(index < 0 || index >= mList.count())
        return;

    emit itemRemoved(index, mList.takeAt(index));
}

void QMJsonArray::removeFirst(void)
{
    this->removeAt(0);
}

void QMJsonArray::removeLast(void)
{
    this->removeAt(mList.count() - 1);
}

QMPointer<QMJsonValue> QMJsonArray::takeFirst(void)
{
    return this->takeAt(0);
}

QMPointer<QMJsonValue> QMJsonArray::takeLast(void)
{
    return this->takeAt(mList.count() - 1);
}

QMPointer<QMJsonValue> QMJsonArray::takeAt(int32_t index)
{
    if(index < 0 || index >= mList.count())
        return QMPointer<QMJsonValue>(new QMJsonValue);

    auto value = mList.takeAt(index);

    emit itemRemoved(index, value);
    return value;
}

QMPointer<QMJsonValue> QMJsonArray::takeAt(int32_t index, const QMPointer<QMJsonValue> &defaultValue)
{
    if(index < 0 || index >= mList.count())
        return defaultValue;

    auto value = mList.takeAt(index);

    emit itemRemoved(index, value);
    return value;
}

QMPointer<QMJsonValue> QMJsonArray::first(void) const
{
    if(mList.isEmpty() == true)
        return QMPointer<QMJsonValue>(new QMJsonValue);

    return mList.first();
}

QMPointer<QMJsonValue> QMJsonArray::last(void) const
{
    if(mList.isEmpty() == true)
        return QMPointer<QMJsonValue>(new QMJsonValue);

    return mList.last();
}

QMPointer<QMJsonValue> QMJsonArray::value(int32_t index) const
{
    if(index < 0 || index >= mList.count())
        return QMPointer<QMJsonValue>(new QMJsonValue);

    return mList.at(index);
}

QMPointer<QMJsonValue> QMJsonArray::value(int32_t index, const QMPointer<QMJsonValue> &defaultValue) const
{
    if(index < 0 || index >= mList.count())
        return defaultValue;

    return mList.at(index);
}

QList<QMPointer<QMJsonValue> > QMJsonArray::values(void) const
{
    return mList;
}

QList<QMPointer<QMJsonValue> > QMJsonArray::mid(int32_t pos, int32_t length) const
{
    if(mList.count() == 0)
        return QList<QMPointer<QMJsonValue> >();

    if(pos < 0) pos = 0;
    if(pos >= mList.count()) pos = mList.count() - 1;

    return mList.mid(pos, length);
}

void QMJsonArray::move(int32_t from, int32_t to)
{
    if(mList.count() == 0)
        return;

    if(to < 0 || to >= mList.count()) return;
    if(from < 0 || from >= mList.count()) return;

    mList.move(from, to);
}

void QMJsonArray::replace(int32_t index, const QMPointer<QMJsonValue> &value)
{
    if(mList.count() == 0)
        return;

    if(index < 0) index = 0;
    if(index >= mList.count()) index = mList.count() - 1;

    mList.replace(index, value);
}

bool QMJsonArray::isBool(int32_t index) const
{
    if(index < 0 || index >= mList.count())
        return false;

    return mList[index]->isBool();
}

bool QMJsonArray::isDouble(int32_t index) const
{
    if(index < 0 || index >= mList.count())
        return false;

    return mList[index]->isDouble();
}

bool QMJsonArray::isString(int32_t index) const
{
    if(index < 0 || index >= mList.count())
        return false;

    return mList[index]->isString();
}

bool QMJsonArray::isArray(int32_t index) const
{
    if(index < 0 || index >= mList.count())
        return false;

    return mList[index]->isArray();
}

bool QMJsonArray::isObject(int32_t index) const
{
    if(index < 0 || index >= mList.count())
        return false;

    return mList[index]->isObject();
}

bool QMJsonArray::toBool(int32_t index) const
{
    return this->value(index)->toBool();
}

double QMJsonArray::toDouble(int32_t index) const
{
    return this->value(index)->toDouble();
}

QString QMJsonArray::toString(int32_t index) const
{
    return this->value(index)->toString();
}

QMPointer<QMJsonArray> QMJsonArray::toArray(int32_t index) const
{
    return this->value(index)->toArray();
}

QMPointer<QMJsonObject> QMJsonArray::toObject(int32_t index) const
{
    return this->value(index)->toObject();
}

bool QMJsonArray::toBool(int32_t index, bool defaultValue) const
{
    return this->value(index)->toBool(defaultValue);
}

double QMJsonArray::toDouble(int32_t index, double defaultValue) const
{
    return this->value(index)->toDouble(defaultValue);
}

QString QMJsonArray::toString(int32_t index, const QString &defaultValue) const
{
    return this->value(index)->toString(defaultValue);
}

QMPointer<QMJsonArray> QMJsonArray::toArray(int32_t index, const QMPointer<QMJsonArray> &defaultValue) const
{
    return this->value(index)->toArray(defaultValue);
}

QMPointer<QMJsonObject> QMJsonArray::toObject(int32_t index, const QMPointer<QMJsonObject> &defaultValue) const
{
    return this->value(index)->toObject(defaultValue);
}

float QMJsonArray::toFloat(int32_t index) const
{
    return this->value(index)->toFloat();
}

char QMJsonArray::toChar(int32_t index) const
{
    return this->value(index)->toChar();
}

unsigned char QMJsonArray::toUChar(int32_t index) const
{
    return this->value(index)->toUChar();
}

short QMJsonArray::toShort(int32_t index) const
{
    return this->value(index)->toShort();
}

unsigned short QMJsonArray::toUShort(int32_t index) const
{
    return this->value(index)->toUShort();
}

int QMJsonArray::toInt(int32_t index) const
{
    return this->value(index)->toInt();
}

unsigned int QMJsonArray::toUInt(int32_t index) const
{
    return this->value(index)->toUInt();
}

long QMJsonArray::toLong(int32_t index) const
{
    return this->value(index)->toLong();
}

unsigned long QMJsonArray::toULong(int32_t index) const
{
    return this->value(index)->toULong();
}

long long QMJsonArray::toLongLong(int32_t index) const
{
    return this->value(index)->toLongLong();
}

unsigned long long QMJsonArray::toULongLong(int32_t index) const
{
    return this->value(index)->toULongLong();
}

float QMJsonArray::toFloat(int32_t index, float defaultValue) const
{
    return this->value(index)->toFloat(defaultValue);
}

char QMJsonArray::toChar(int32_t index, char defaultValue) const
{
    return this->value(index)->toChar(defaultValue);
}

unsigned char QMJsonArray::toUChar(int32_t index, unsigned char defaultValue) const
{
    return this->value(index)->toUChar(defaultValue);
}

short QMJsonArray::toShort(int32_t index, short defaultValue) const
{
    return this->value(index)->toShort(defaultValue);
}

unsigned short QMJsonArray::toUShort(int32_t index, unsigned short defaultValue) const
{
    return this->value(index)->toUShort(defaultValue);
}

int QMJsonArray::toInt(int32_t index, int defaultValue) const
{
    return this->value(index)->toInt(defaultValue);
}

unsigned int QMJsonArray::toUInt(int32_t index, unsigned int defaultValue) const
{
    return this->value(index)->toUInt(defaultValue);
}

long QMJsonArray::toLong(int32_t index, long defaultValue) const
{
    return this->value(index)->toLong(defaultValue);
}

unsigned long QMJsonArray::toULong(int32_t index, unsigned long defaultValue) const
{
    return this->value(index)->toULong(defaultValue);
}

long long QMJsonArray::toLongLong(int32_t index, long long defaultValue) const
{
    return this->value(index)->toLongLong(defaultValue);
}

unsigned long long QMJsonArray::toULongLong(int32_t index, unsigned long long defaultValue) const
{
    return this->value(index)->toULongLong(defaultValue);
}

bool QMJsonArray::fromBool(int32_t index, bool value)
{
    return this->value(index)->fromBool(value);
}

bool QMJsonArray::fromDouble(int32_t index, double value)
{
    return this->value(index)->fromDouble(value);
}

bool QMJsonArray::fromString(int32_t index, const QString &value)
{
    return this->value(index)->fromString(value);
}

bool QMJsonArray::fromArray(int32_t index, const QMPointer<QMJsonArray> &value)
{
    return this->value(index)->fromArray(value);
}

bool QMJsonArray::fromObject(int32_t index, const QMPointer<QMJsonObject> &value)
{
    return this->value(index)->fromObject(value);
}

bool QMJsonArray::fromFloat(int32_t index, float value)
{
    return this->value(index)->fromFloat(value);
}

bool QMJsonArray::fromChar(int32_t index, char value)
{
    return this->value(index)->fromChar(value);
}

bool QMJsonArray::fromUChar(int32_t index, unsigned char value)
{
    return this->value(index)->fromUChar(value);
}

bool QMJsonArray::fromShort(int32_t index, short value)
{
    return this->value(index)->fromShort(value);
}

bool QMJsonArray::fromUShort(int32_t index, unsigned short value)
{
    return this->value(index)->fromUShort(value);
}

bool QMJsonArray::fromInt(int32_t index, int value)
{
    return this->value(index)->fromInt(value);
}

bool QMJsonArray::fromUInt(int32_t index, unsigned int value)
{
    return this->value(index)->fromUInt(value);
}

bool QMJsonArray::fromLong(int32_t index, long value)
{
    return this->value(index)->fromLong(value);
}

bool QMJsonArray::fromULong(int32_t index, unsigned long value)
{
    return this->value(index)->fromULong(value);
}

bool QMJsonArray::fromLongLong(int32_t index, long long value)
{
    return this->value(index)->fromLongLong(value);
}

bool QMJsonArray::fromULongLong(int32_t index, unsigned long long value)
{
    return this->value(index)->fromULongLong(value);
}

QDebug operator<<(QDebug dbg, const QMJsonArray &array)
{
    QDebugStateSaver saver(dbg);
    auto started = false;

    dbg.nospace() << "QMJsonArray[";

    for(const auto &value : array.values())
    {
        if(started == true)
            dbg << ",";

        dbg << value;
        started = true;
    }

    return dbg << "]";
}

QDebug operator<<(QDebug dbg, const QMPointer<QMJsonArray> &value)
{
    if(value.isNull() == true)
    {
        QDebugStateSaver saver(dbg);

        dbg.nospace() << "QMPointer<";
        dbg << "QMJsonArray" << ">: NULL";

        return dbg;
    }
    else
    {
        return dbg << *value;
    }
}
