#pragma once

using namespace System;

public ref class Label
{
public:
	Label(const CLabel& mfcLabel)
	{
		MediumUrl = gcnew String(mfcLabel.GetMediumUrl());
		LargeUrl = gcnew String(mfcLabel.GetLargeUrl());
	}

	static Label^ CreateDesignTimeInstance()
	{
		Label^ label = gcnew Label();

		label->MediumUrl = "http://cache.wine.com/labels/92192m.jpg";
		label->LargeUrl = "http://cache.wine.com/labels/92192l.jpg";

		return label;
	}

	property String^ MediumUrl
	{
	public:
		String^ get() { return m_mediumUrl; }
	private:
		void set(String^ mediumUrl) { m_mediumUrl = mediumUrl; }
	}

	property String^ LargeUrl
	{
	public:
		String^ get() { return m_largeUrl; }
	private:
		void set(String^ largeUrl) { m_largeUrl = largeUrl; }
	}

private:
	Label()
	{
	}

	String^ m_mediumUrl;
	String^ m_largeUrl;
};
