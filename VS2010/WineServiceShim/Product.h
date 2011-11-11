#pragma once

using namespace System;

#include "Label.h"
#include "GeoLocation.h"

public ref class Product
{
public:
	Product(const CProduct& mfcProduct)
	{
		Id = gcnew String(mfcProduct.GetId());
		Name = gcnew String(mfcProduct.GetName());
		Description = gcnew String(mfcProduct.GetDescription());
		PriceMin = mfcProduct.GetPriceMin();
		PriceMax = mfcProduct.GetPriceMax();
		PriceRetail = mfcProduct.GetPriceRetail();
		Type = gcnew String(mfcProduct.GetType());
		Url = gcnew String(mfcProduct.GetUrl());
		Vintage = gcnew String(mfcProduct.GetVintage());
		Year = gcnew String(mfcProduct.GetYear());

		ProductLabel = gcnew Label(*mfcProduct.GetLabel().get());
		ProductGeoLocation = gcnew GeoLocation(*mfcProduct.GetGeoLocation().get());
	}

	static Product^ CreateDesignTimeInstance()
	{
		Product^ product = gcnew Product();

        product->Id = "92192";
        product->Name = "Chateau Mont Redon Cotes-du-Rhone 2005";
        product->Description = String::Empty;
        product->PriceMin = 12.29;
        product->PriceMax = 19.29;
        product->PriceRetail = 12.29;
        product->Type = "Wine";
        product->Url = "http://www.wine.com/V6/Chateau-Mont-Redon-Cotes-du-Rhone-2005/wine/92192/detail.aspx";
        product->Vintage = "2005";
        product->Year = String::Empty;

		product->ProductLabel = Label::CreateDesignTimeInstance();

		return product;
	}

	property String^ Id
	{
	public:
		String^ get() { return m_id; }
	private:
		void set(String^ id) { m_id = id; }
	}

	property String^ Name
	{
	public:
		String^ get() { return m_name; }
	private:
		void set(String^ name) { m_name = name; }
	}

	property String^ Description
	{
	public:
		String^ get() { return m_description; }
	private:
		void set(String^ description) { m_description = description; }
	}

	property double PriceMin
	{
	public:
		double get() { return m_priceMin; }
	private:
		void set(double priceMin) { m_priceMin = priceMin; }
	}

	property double PriceMax
	{
	public:
		double get() { return m_priceMax; }
	private:
		void set(double priceMax) { m_priceMax = priceMax; }
	}

	property double PriceRetail
	{
	public:
		double get() { return m_priceRetail; }
	private:
		void set(double priceRetail) { m_priceRetail = priceRetail; }
	}

	property String^ Type
	{
	public:
		String^ get() { return m_type; }
	private:
		void set(String^ type) { m_type = type; }
	}

	property String^ Url
	{
	public:
		String^ get() { return m_url; }
	private:
		void set(String^ url) { m_url = url; }
	}

	property String^ Vintage
	{
	public:
		String^ get() { return m_vintage; }
	private:
		void set(String^ vintage) { m_vintage = vintage; }
	}

	property String^ Year
	{
	public:
		String^ get() { return m_year; }
	private:
		void set(String^ year) { m_year = year; }
	}

	property Label^ ProductLabel
	{
	public:
		Label^ get() { return m_label; }
	private:
		void set(Label^ label) { m_label = label; }
	}

	property GeoLocation^ ProductGeoLocation
	{
	public:
		GeoLocation^ get() { return m_geoLocation; }
	private:
		void set(GeoLocation^ geoLocation) { m_geoLocation = geoLocation; }
	}

private:
	Product()
	{
		ProductLabel = nullptr;
		ProductGeoLocation = nullptr;
	}

	String^ m_id;
	String^ m_name;
	String^ m_description;
	double m_priceMin;
	double m_priceMax;
	double m_priceRetail;
	String^ m_type;
	String^ m_url;
	String^ m_vintage;
	String^ m_year;
	Label^ m_label;
	GeoLocation^ m_geoLocation;
};
