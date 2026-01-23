import { useState, useEffect } from 'react';
import ReactMarkdown from 'react-markdown';
import remarkGfm from 'remark-gfm';
import welcomeContent from '../docs/welcome.md?raw';
import programContent from '../docs/program.md?raw';
import plannedContent from '../docs/planned.md?raw';
import './InfoPage.css';

const tabs = [
  { id: 'welcome', label: 'Welcome', content: welcomeContent },
  { id: 'programming', label: 'Programming', content: programContent },
  { id: 'planned', label: 'Planned Changes', content: plannedContent },
];

export default function InfoPage({ onBack, initialTab = 'welcome' }) {
  const [activeTab, setActiveTab] = useState(initialTab);

  useEffect(() => {
    setActiveTab(initialTab);
  }, [initialTab]);

  const activeContent = tabs.find(tab => tab.id === activeTab)?.content || '';

  return (
    <div className="info-page">
      <nav className="info-nav">
        {tabs.map(tab => (
          <button
            key={tab.id}
            className={`info-nav__tab ${activeTab === tab.id ? 'active' : ''}`}
            onClick={() => setActiveTab(tab.id)}
          >
            {tab.label}
          </button>
        ))}
      </nav>
      
      <div className="info-content">
        <ReactMarkdown remarkPlugins={[remarkGfm]}>{activeContent}</ReactMarkdown>
      </div>
    </div>
  );
}
