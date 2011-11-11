#pragma once

using namespace System;

public ref class GeoLocation
{
public:
	GeoLocation(const CGeoLocation& mfcGeoLocation)
	{
		Longitude = gcnew String(mfcGeoLocation.GetLongitude());
		Latitude = gcnew String(mfcGeoLocation.GetLatitude());
		Url = gcnew String(mfcGeoLocation.GetUrl());
	}

	property String^ Longitude
	{
	public:
		String^ get() { return m_longitude; }
	private:
		void set(String^ longitude) { m_longitude = longitude; }
	}

	property String^ Latitude
	{
	public:
		String^ get() { return m_latitude; }
	private:
		void set(String^ latitude) { m_latitude = latitude; }
	}

	property String^ Url
	{
	public:
		String^ get() { return m_url; }
	private:
		void set(String^ url) { m_url = url; }
	}

private:
	String^ m_longitude;
	String^ m_latitude;
	String^ m_url;
};
